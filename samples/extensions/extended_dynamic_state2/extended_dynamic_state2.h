/* Copyright (c) 2019, Arm Limited and Contributors
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

#pragma once

#include "api_vulkan_sample.h"

class ExtendedDynamicState2 : public ApiVulkanSample
{
  public:
	struct
	{
		bool      depth_bias_enable         = false;
		bool      primitive_restart_enable  = false;
		bool      rasterizer_discard_enable = false;
		int32_t   logic_op_index{};
		VkLogicOp logicOp = VK_LOGIC_OP_CLEAR;
		float     patch_control_points_float{};
		uint32_t  patch_control_points{};
	} gui_settings;

	std::vector<std::string> logic_op_object_names{"CLEAR",
	                                               "AND",
	                                               "AND_REVERSE",
	                                               "COPY",
	                                               "AND_INVERTED",
	                                               "NO_OP",
	                                               "XOR",
	                                               "OR",
	                                               "NOR",
	                                               "EQUIVALENT",
	                                               "INVERT",
	                                               "OR_REVERSE",
	                                               "COPY_INVERTED",
	                                               "OR_INVERTED",
	                                               "NAND",
	                                               "SET"};

	struct
	{
		Texture envmap;
	} textures;

	struct UBOVS
	{
		glm::mat4 projection;
		glm::mat4 modelview;
		glm::mat4 skybox_modelview;
		float     modelscale = 0.15f;
	} ubo_vs;

	VkPipelineLayout                                   pipeline_layout{VK_NULL_HANDLE};
	VkPipeline                                         model_pipeline{VK_NULL_HANDLE};
	VkPipeline                                         skybox_pipeline{VK_NULL_HANDLE};
	VkPhysicalDeviceExtendedDynamicState2FeaturesEXT   extended_dynamic_state2_features{};
	VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT graphics_pipeline_library{};
	VkVertexInputBindingDescription2EXT                vertex_bindings_description_ext{};
	VkVertexInputAttributeDescription2EXT              vertex_attribute_description_ext[2]{};

	VkDescriptorSet       descriptor_set{VK_NULL_HANDLE};
	VkDescriptorSetLayout descriptor_set_layout{VK_NULL_HANDLE};
	VkDescriptorPool      descriptor_pool{VK_NULL_HANDLE};

	std::unique_ptr<vkb::sg::SubMesh>  skybox;
	std::unique_ptr<vkb::sg::SubMesh>  object;
	std::unique_ptr<vkb::core::Buffer> ubo;

	ExtendedDynamicState2();
	~ExtendedDynamicState2();

	virtual void render(float delta_time) override;
	virtual void build_command_buffers() override;
	virtual bool prepare(vkb::Platform &platform) override;
	virtual void request_gpu_features(vkb::PhysicalDevice &gpu) override;
	virtual void on_update_ui_overlay(vkb::Drawer &drawer) override;

	void prepare_uniform_buffers();
	void update_uniform_buffers();
	void create_pipeline();
	void draw();

	void load_assets();
	void create_descriptor_pool();
	void setup_descriptor_set_layout();
	void create_descriptor_sets();

#if VK_NO_PROTOTYPES
	PFN_vkCmdSetDepthBiasEnableEXT         vkCmdSetDepthBiasEnableEXT{VK_NULL_HANDLE};
	PFN_vkCmdSetLogicOpEXT                 vkCmdSetLogicOpEXT{VK_NULL_HANDLE};
	PFN_vkCmdSetPatchControlPointsEXT      vkCmdSetPatchControlPointsEXT{VK_NULL_HANDLE};
	PFN_vkCmdSetPrimitiveRestartEnableEXT  vkCmdSetPrimitiveRestartEnableEXT{VK_NULL_HANDLE};
	PFN_vkCmdSetRasterizerDiscardEnableEXT vkCmdSetRasterizerDiscardEnableEXT{VK_NULL_HANDLE};
#endif
};

std::unique_ptr<vkb::VulkanSample> create_extended_dynamic_state2();
