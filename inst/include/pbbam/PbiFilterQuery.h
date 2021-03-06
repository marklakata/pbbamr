// Copyright (c) 2014-2015, Pacific Biosciences of California, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted (subject to the limitations in the
// disclaimer below) provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//  * Neither the name of Pacific Biosciences nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
// GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY PACIFIC
// BIOSCIENCES AND ITS CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL PACIFIC BIOSCIENCES OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
// USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//
// File Description
/// \file PbiFilterQuery.h
/// \brief Defines the PbiFilterQuery class.
//
// Author: Derek Barnett

#ifndef PBIFILTERQUERY_H
#define PBIFILTERQUERY_H

#include "pbbam/Config.h"
#include "pbbam/PbiFilter.h"
#include "pbbam/internal/QueryBase.h"
#include <vector>

namespace PacBio {
namespace BAM {

/// \brief The PbiFilter class provides iterable access to a DataSet's %BAM
///        records, limiting results to those matching filter criteria.
///
/// Example:
/// \include code/PbiFilterQuery.txt
///
/// \note Currently, all %BAM files must have a corresponding ".pbi" index file.
///       Use BamFile::EnsurePacBioIndexExists before creating the query if one
///       may not be present.
///
class PBBAM_EXPORT PbiFilterQuery : public internal::IQuery
{
public:
    /// \brief Creates a new PbiFilterQuery, limiting record results to only
    ///        those matching filter criteria
    ///
    /// \param[in] filter   filtering criteria
    /// \param[in] dataset  input data source(s)
    ///
    /// \throws std::runtime_error on failure to open/read underlying %BAM or
    ///         PBI files.
    ///
    PbiFilterQuery(const PbiFilter& filter, const DataSet& dataset);

    ~PbiFilterQuery(void);

public:

    /// \brief Main iteration point for record access.
    ///
    /// Most client code should not need to use this method directly. Use
    /// iterators instead.
    ///
    bool GetNext(BamRecord& r);

private:
    struct PbiFilterQueryPrivate;
    std::unique_ptr<PbiFilterQueryPrivate> d_;
};

} // namespace BAM
} // namespace PacBio

#endif // PBIFILTERQUERY_H
