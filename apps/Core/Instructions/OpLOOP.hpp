/*
 *
 *  Copyright (c) 2015 Stanislav Zhukov (koncord@rwa.su)
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#ifndef YAPE_OPLOOP_HPP
#define YAPE_OPLOOP_HPP

#include "OpJMP.hpp"

class OpLOOP : public OpJMP
{
public:
    bool Condition() const override;
    int GetOpcode() const override;
    bool isConstDestinationAllowed() const final;
};


#endif //YAPE_OPLOOP_HPP
