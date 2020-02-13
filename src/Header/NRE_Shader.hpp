
    /**
     * @file Header/NRE_Shader.hpp
     * @brief Declaration of NearlyRealEngine's Shader Header
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "../Renderer/Program/Uniforms/NRE_Uniforms.hpp"
    #include "../Renderer/Program/Shader/NRE_Shader.hpp"
    #include "../Renderer/Program/Shader/Vertex/NRE_VertexShader.hpp"
    #include "../Renderer/Program/Shader/Fragment/NRE_FragmentShader.hpp"
    #include "../Renderer/Program/Shader/Geometry/NRE_GeometryShader.hpp"

    #include "../Renderer/Program/Core/Primitive/2D/NRE_Primitive2D.hpp"
    #include "../Renderer/Program/Core/Primitive/3D/NRE_Primitive3D.hpp"
    #include "../Renderer/Program/Core/Primitive/Instanced3D/NRE_InstancedPrimitive3D.hpp"
    
    #include "../Renderer/Program/Core/Water/NRE_Water.hpp"
    #include "../Renderer/Program/Core/GBuffer/GBuffer/NRE_GBuffer.hpp"
    #include "../Renderer/Program/Core/GBuffer/InstancedGBuffer/NRE_InstancedGBuffer.hpp"

    #include "../Renderer/Program/Core/Shadow/Shadow/NRE_Shadow.hpp"
    #include "../Renderer/Program/Core/Shadow/InstancedShadow/NRE_InstancedShadow.hpp"
    
    #include "../Renderer/Program/Core/PBR/NRE_PBR.hpp"
    
    #include "../Renderer/Program/Core/SSAO/NRE_SSAOEffect.hpp"
    
    #include "../Renderer/Program/Core/IBL/BRDF/NRE_BRDF.hpp"
    #include "../Renderer/Program/Core/IBL/Irradiance/NRE_Irradiance.hpp"
    #include "../Renderer/Program/Core/IBL/Prefilter/NRE_Prefilter.hpp"
    
    #include "../Renderer/Program/Core/SkyBox/Capture/NRE_Capture.hpp"
    #include "../Renderer/Program/Core/SkyBox/SkyBox/NRE_SkyBox.hpp"

    #include "../Renderer/Program/Core/Debug/Normal/NRE_DebugNormal.hpp"

    #include "../Renderer/Program/Manager/NRE_ProgramManager.hpp"
