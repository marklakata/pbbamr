% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/utils.R
\name{loadAlnsFromIndex}
\alias{loadAlnsFromIndex}
\title{Given a data frame returned by loadPBI and a fasta file, load a list of alignments}
\usage{
loadAlnsFromIndex(index, indexed_fasta_name, rows = NULL)
}
\arguments{
\item{index}{A data frame returned by loadPBI}

\item{indexed_fasta_name}{A character vector for the returned fasta file.}

\item{rows}{A list of rows to select the data from (default = use all data)}
}
\value{
A list of alignments as data frames
}
\description{
Given a data frame returned by loadPBI and a fasta file, load a list of alignments
}
\seealso{
loadReadsFromIndex
}

