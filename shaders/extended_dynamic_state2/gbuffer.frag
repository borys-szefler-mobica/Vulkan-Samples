/* Copyright (c) 2022, Mobica Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 the "License";
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#version 450

layout(binding = 1) uniform samplerCube samplerEnvMap;

layout(location = 0) in vec3 inUVW;
layout(location = 1) in vec3 inPos;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inViewVec;
layout(location = 4) in vec3 inLightVec;
layout(location = 5) in mat4 inInvModelView;

layout(location = 0) out uvec4 outColor0;

layout(constant_id = 0) const int type = 0;

#define PI 3.1415926
#define TwoPI (2.0 * PI)

void main()
{
	vec4 color;
	vec3 wcNormal;

	switch (type)
	{
		case 0:
		case 1:
		case 2:
		{
			vec3 normal = normalize(inUVW);
			color       = texture(samplerEnvMap, normal);
		}
		break;
	}

	outColor0.rgb = floatBitsToUint(color.rgb);
}