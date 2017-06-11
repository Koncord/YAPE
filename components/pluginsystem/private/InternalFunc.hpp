/*
 *
 *  Copyright (c) 2015-2017 Stanislav Zhukov
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

#ifndef YAPE_INTERNALFUNC_HPP
#define YAPE_INTERNALFUNC_HPP

int internal_PipeSend(uint32_t id, void *date, uint32_t size) noexcept;

/**
 * \brief return and increment loaded id and name of plugin.
 * \param[out] id plugin id.
 * \param[out] name plugin name.
 **/
void internal_GetPluginSearchNext(uint32_t *id, char **name) noexcept;

/**
 * \brief reset internal counter of plugins.
 **/
void internal_GetPluginSearchReset() noexcept;

#endif //YAPE_INTERNALFUNC_HPP
