
    #version 450

    in vec2 uv;
    in mat3 TBN;
    in vec4 vertexAndId;
    in vec3 normal;

    uniform sampler2DArray texNormal;

    out vec4 [2] fragData;

    void main() {
        vec2 outUV = mix(uv, fract(vec2(dot(normal.zxy, vertexAndId.xyz), dot(normal.yzx, vertexAndId.xyz))), uv == vec2(-1.0, -1.0));
        vec4 outNormal = texture(texNormal, vec3(outUV, vertexAndId.w));
        outNormal = normalize(outNormal * 2.0 - 1.0);
        outNormal = normalize(vec4(TBN * outNormal.xyz, 1.0));
        outNormal.w = vertexAndId.w;
	    fragData[0] = vec4(outUV, 0.0, 1.0);
        fragData[1] = outNormal;
    }
