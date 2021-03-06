// Copyright (c) 2016, Pacific Biosciences of California, Inc.
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
/// \file BamRecordTags.h
/// \brief Defines the BamRecordTags utility class.
//
// Author: Derek Barnett

#ifndef BAMRECORDTAGS_H
#define BAMRECORDTAGS_H

#include "pbbam/BamRecord.h"
#include "pbbam/BamRecordImpl.h"
#include "pbbam/BamRecordTag.h"
#include "EnumClassHash.h"
#include <string>
#include <unordered_map>
#include <cassert>

namespace PacBio {
namespace BAM {
namespace internal {

class BamRecordTags
{
public:
    // tag info
    static inline bool IsPulse(const BamRecordTag tag);
    static inline std::string LabelFor(const BamRecordTag tag);

private:
    struct BamRecordTagData
    {
        const std::string label_; //[3]; // 2-char tag plus NULL
        const bool isPulse_;
    };
    typedef std::unordered_map<BamRecordTag,
                               BamRecordTagData,
                               EnumClassHash> TagLookupType;

    static const TagLookupType tagLookup;
};

inline bool BamRecordTags::IsPulse(const BamRecordTag tag)
{
    assert(tagLookup.find(tag) != tagLookup.cend());
    return tagLookup.at(tag).isPulse_;
}

inline std::string BamRecordTags::LabelFor(const BamRecordTag tag)
{
    assert(tagLookup.find(tag) != tagLookup.cend());
    return tagLookup.at(tag).label_;
}

} // namespace internal
} // namespace BAM
} // namespace PacBio

#endif // BAMRECORDTAGS_H
