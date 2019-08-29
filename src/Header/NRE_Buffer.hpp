
    /**
     * @file Header/NRE_Buffer.hpp
     * @brief Declaration of NearlyRealEngine's Buffer Header
     * @author Louis ABEL
     * @date 18/09/2018
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "../GL/Buffer/FrameBuffer/NRE_FrameBuffer.hpp"
    #include "../GL/VBO/NRE_AbstractVBO.hpp"
    #include "../GL/VBO/Layout/NRE_Layout.hpp"
    #include "../GL/VBO/Layout/Primitive/NRE_PrimitiveVertex.hpp"
    #include "../GL/VBO/NRE_VBO.hpp"
    #include "../GL/VBO/IBO/NRE_IBO.hpp"
    #include "../GL/FBO/NRE_FBO.hpp"
    #include "../GL/Buffer/VAO/NRE_VAO.hpp"
    #include "../GL/Buffer/Array/NRE_ArrayBuffer.hpp"
    #include "../GL/Buffer/Array/Attribute/NRE_AttributeBuffer.hpp"
    #include "../GL/Buffer/Array/Element/NRE_ElementBuffer.hpp"
    #include "../GL/Buffer/Array/Uniform/NRE_UniformBuffer.hpp"
    #include "../GL/Buffer/Attachable/NRE_Attachable.hpp"
    #include "../GL/Buffer/Attachable/RenderBuffer/NRE_RenderBuffer.hpp"
    #include "../GL/Buffer/Attachable/Texture/NRE_TextureBuffer.hpp"
    #include "../GL/Buffer/Attachable/Texture/2D/NRE_Texture2DBuffer.hpp"
    #include "../GL/Buffer/Attachable/Texture/3D/NRE_Texture3DBuffer.hpp"
    #include "../GL/Buffer/Attachable/Texture/CubeMap/NRE_CubeMap.hpp"
