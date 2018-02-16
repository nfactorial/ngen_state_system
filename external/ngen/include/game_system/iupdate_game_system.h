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

#ifndef NGEN_CORE_IUPDATE_GAME_SYSTEM_H
#define NGEN_CORE_IUPDATE_GAME_SYSTEM_H

////////////////////////////////////////////////////////////////////////////

namespace ngen {
    struct UpdateArgs;

    //! \brief Interface that is implemented by game systems that require their onUpdate method to be invoked
    //! each frame update.
    //!
    struct IUpdateGameSystem {
        virtual void onUpdate(const UpdateArgs &updateArgs) = 0;
    };
}

////////////////////////////////////////////////////////////////////////////

#endif //NGEN_CORE_IUPDATE_GAME_SYSTEM_H
