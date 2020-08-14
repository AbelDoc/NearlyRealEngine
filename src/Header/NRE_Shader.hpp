
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
    
    #include "../Renderer/Program/Core/GBuffer/ModelShader/NRE_ModelShader.hpp"
    #include "../Renderer/Program/Core/GBuffer/VoxelShader/NRE_VoxelShader.hpp"

    #include "../Renderer/Program/Core/PBR/NRE_PBR.hpp"
    
    #include "../Renderer/Program/Core/SSAO/NRE_SSAOEffect.hpp"
    
    #include "../Renderer/Program/Core/IBL/BRDF/NRE_BRDF.hpp"
    #include "../Renderer/Program/Core/IBL/Irradiance/NRE_Irradiance.hpp"
    #include "../Renderer/Program/Core/IBL/Prefilter/NRE_Prefilter.hpp"
    
    #include "../Renderer/Program/Core/SkyBox/Capture/NRE_Capture.hpp"
    #include "../Renderer/Program/Core/SkyBox/SkyBox/NRE_SkyBox.hpp"

    #include "../Renderer/Program/Manager/NRE_ProgramManager.hpp"
