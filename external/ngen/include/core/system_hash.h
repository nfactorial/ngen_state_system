//
// Copyright 2017 nfactorial
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef NGEN_CORE_SYSTEM_HASH_H
#define NGEN_CORE_SYSTEM_HASH_H

////////////////////////////////////////////////////////////////////////////

#include <cstddef>


////////////////////////////////////////////////////////////////////////////

namespace ngen {
    // Simple implementation of the Fowler-Noll-Vo hash, this is generally just used to hash system names
    // and state names within the state tree. So we don't need anything super crypto as we're unlikely to
    // have that many strings.
    // More information: https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    template <typename TType, TType TPrime> class TSystemHash {
    public:
        static inline TType compute(const char * const data) {
            TType hash = 0;

            if (data) {
                for (size_t loop = 0; data[loop]; ++loop) {
                    const auto next = data[loop];
                    hash = (hash ^ next) * TPrime;
                }
            }

            return hash;
        }
    };
}

////////////////////////////////////////////////////////////////////////////

#endif //NGEN_CORE_SYSTEM_HASH_H
