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

#ifndef NGEN_CORE_IGAME_SYSTEM_H
#define NGEN_CORE_IGAME_SYSTEM_H

////////////////////////////////////////////////////////////////////////////

namespace ngen {
    struct InitArgs;
    struct UpdateArgs;

    //! \brief Interface that defines the basic details of a game system that may be registered with the engine.
    //!
    //! Game systems represent a unit of code that performs a block of processing in the running application.
    //! Systems are assigned to game states within the running titles state tree, whilst active the systems
    //! onUpdate method is invoked each frame.
    //!
    //! When a system becomes active within the title, its onActivate method will be invoked allowing the system
    //! to perform any processing necessary prior to its execution.
    //!
    //! When a system becomes in-active within the title, its onDeactivate method will be invoked allowing the system
    //! to perform any processing necessary prior to terminating its execution.
    //!
    //! A systems onInitialize method is invoked once the state tree has been constructed. At this point, it should
    //! consider its properties valid. However, if a system references another system object is should not consider
    //! the object referenced to be valid at that time.
    //!
    struct IGameSystem {
        virtual void onDestroy() = 0;
        virtual void onInitialize(const InitArgs &initArgs) = 0;

        virtual void onActivate() = 0;
        virtual void onDeactivate() = 0;

        virtual void onUpdate(const UpdateArgs &updateArgs) = 0;
    };
}

////////////////////////////////////////////////////////////////////////////

#endif //NGEN_CORE_IGAME_SYSTEM_H
