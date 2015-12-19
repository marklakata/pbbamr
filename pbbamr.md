---
title: "Examining PacBio data with pbbamr"
author: "Nigel Delaney"
date: '2015-12-18'
output: html_document
vignette: |
  %\VignetteIndexEntry{Examining PacBio data with pbbamr} %\VignetteEngine{knitr::rmarkdown} %\VignetteEncoding{UTF-8}
---

This package examines aligned data in the PacBio BAM format.  It can be used to 
investigate the BAM pbi index file to get bulk alignment statistics, or can be
used for deeper analysis of individual alignments by directly accessing
the BAM file alignments.

## Package installation

```
install.packages("devtools")
library(devtools)
install_github("evolvedmicrobe/pbbamr")
```

## Loading and plotting pbi files

Simply pass a BAM file name to the `loadpbi` function (the pbi file must exist
as the filename + ".pbi") which will return a data frame with the information
available in the pbi file.


```r
library(pbbamr)
# For this example, we will load some sample data
# distributed with the package.
bamname = system.file("extdata", "bam_mapping_1.bam", package="pbbamr")
# Load the index table.
ind = loadpbi(bamname)
# Show the first 3 rows (transposed, note kable just formats)
knitr::kable(t(ind[1:3,]))
```



|           |1        |2        |3        |
|:----------|:--------|:--------|:--------|
|hole       |49050    |32328    |6469     |
|qstart     |48       |0        |9936     |
|qend       |1132     |344      |10187    |
|qual       |0        |0        |0        |
|offset     |32636928 |32645486 |32648388 |
|flag       |0        |0        |0        |
|ref        |0        |0        |0        |
|tstart     |0        |675      |2170     |
|tend       |471      |1026     |2397     |
|astart     |653      |1        |9960     |
|aend       |1129     |344      |10185    |
|rc         |00       |00       |01       |
|matches    |460      |339      |216      |
|mismatches |0        |0        |0        |
|mq         |254      |254      |254      |
|inserts    |16       |4        |9        |
|dels       |11       |12       |11       |

The fields in the data frame closely correspond to the [published documentation
of the
format](http://pacbiofileformats.readthedocs.org/en/latest/PacBioBamIndex.html).
Note that because R does cannot represent long integers, we store the file offset
as a string (which is a detail you can ignore).


The PacBio index table can tell you a lot about the data.  For example we plot a
distribution of alignment length and accuracy below.

**Alignment Length Distributions**


```r
library(ggplot2)
# We can calculate the length of the alignment on the reference as 
# the template end minus the template start of that alignment.
ind$alnLength = ind$tend - ind$tstart
ggplot(ind, aes(x=alnLength)) + geom_density(fill="blue") + theme_bw() +
  labs(x="Alignment Length on Reference")
```

![plot of chunk unnamed-chunk-2](figure/unnamed-chunk-2-1.png) 

**Accuracy Distribution**

Accuracy is a metric with many possible definitions.  Below, we will examine an
error rate defined as the total number of errors per reference basepair.


```r
ind$errorRate = (ind$mismatches + ind$inserts + ind$dels) / ind$alnLength 
ggplot(ind, aes(x=errorRate)) + geom_density(fill="cyan") + theme_bw() +
  labs(x="Error Rate")
```

![plot of chunk unnamed-chunk-3](figure/unnamed-chunk-3-1.png) 


## Examining Individual Alignments

Given an index file, we may want to drill down and examine the individul
alignments.  `pbbamr` allows you to do this if you have an indexed fasta file of
the reference available.  The function `loadDataAtOffsets` will take a list of
file offsets (from the pbi index file) and return each BAM record specified by a
file offset as a data frame with rows corresponding to alignment positions and
columns as read or reference bases.


```r
# Get the name of the sample indexed FASTA file
fastaname = system.file("extdata", "lambdaNEB.fa", package="pbbamr")
# let's just grab and plot one alignment.
allAlns = loadDataAtOffsets(ind$offset[1], bamname, fastaname)
# The alignments are returned as a list of data frames
# in this case let's just look at the first
aln = allAlns[[1]]
head(aln[1:6,])
```

```
##   read ref
## 1    G   G
## 2    G   G
## 3    G   G
## 4    C   C
## 5    G   G
## 6    G   G
```

Each alignment (or BAM record) is returned as a data frame element of a list. 
With this, one could combine all of these into one super alignment to gain
statistics.  For example, let's validate that the number of insertions in the
alignments matches the pbi file.



```r
# Get all the alignments for all records in the index
allAlns = loadDataAtOffsets(ind$offset, bamname, fastaname)
# let's combine the individual alignments into one big data frame
alns = do.call(rbind, allAlns)
# Now count the number of insertions
insert_cnt = sum(alns$ref=="-")
# Do they match the pbi file?
insert_cnt == sum(ind$inserts)
## [1] TRUE
```

More usefully though, one may want to perform some operation over a set of 
alignments to gather some summary statistics from them.  For example, let's 
write a cheesy function to figure out for single deletion events which basepair
was deleted and which basepair followed that deletion.


```r
# First let's write a function to find single deletion events, and report 
# the deleted base and following base.
findSingleDeletions <- function(aln) {
  # Where are the deletions of size 1?
  # First we will convert it to run length encoding (gap = 5)
  rls = rle(as.integer(aln$read))
  # Now find out what has a deletion of size 1
  del_size1 = which(rls$values == 5 & rls$lengths == 1)
  # and convert back from run length to standard coordinates
  org_positions = cumsum(rls$lengths)
  single_del_locs = org_positions[del_size1]
  # Presumably the alignment should not end with 
  # a deletion, but let's be sure
  single_del_locs = single_del_locs[single_del_locs < nrow(aln)]
  # And now let's grab the deleted base and the one after
  data.frame(AfterDeletion = aln$ref[single_del_locs + 1], 
             Deleted = aln$ref[single_del_locs])
}
# Apply our function to investigate deletions to all alignments
deletions = lapply(allAlns, findSingleDeletions)
# Combine the results
dels = do.call(rbind, deletions)
# And examine the table
knitr::kable(table(dels$AfterDeletion, dels$Deleted))
```



|   |   A|   C|   G|   T|  -|
|:--|---:|---:|---:|---:|--:|
|A  | 126|  38|  53|  18|  0|
|C  |  29| 222|  86|  42|  0|
|G  |  42|  29| 330|  59|  0|
|T  |  45|  26|  75| 106|  0|
|-  |   0|   0|   0|   0|  0|

```r
# Tables can also be visualized as heatmaps
dels$Count = 1
agg = aggregate(Count ~ AfterDeletion + Deleted, dels, length )
ggplot(agg, aes(x=AfterDeletion, y=Deleted, fill=Count)) + geom_tile() +
  theme_bw(base_size=10)  + 
  labs(title="Anyone think G/C homopolymers\nwill be hard in consensus?",
       x="Base After Deletion", y="Deleted Base")
```

![plot of chunk unnamed-chunk-6](figure/unnamed-chunk-6-1.png) 
  
    
