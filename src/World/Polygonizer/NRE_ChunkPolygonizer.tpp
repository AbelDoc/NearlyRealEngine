
    /**
     * @file NRE_ChunkPolygonizer.tpp
     * @brief Implementation of Engine's World's Object : ChunkPolygonizer
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace World {

            void ChunkPolygonizer::polygonize(Chunk const& target, GL::VBO<GL::PrimitiveVertex>& ibo) {
                Math::Point3D<float> vertices[12];

                std::size_t index = 0;

                for (float y = 0; y <= Chunk::SIZE_Y - target.getResolution(); y += target.getResolution()) {
                    for (float z = 0; z <= Chunk::SIZE_Z - target.getResolution(); z += target.getResolution()) {
                        for (float x = 0; x <= Chunk::SIZE_X - target.getResolution(); x += target.getResolution()) {
                            Cell const& cell = target[index++];
                            Math::Vector3D<float> cellShift = Math::Vector3D<float>(x, y, z) + target.getPosition();
                            if (edgeTable[cell] != 0) {
                                if (edgeTable[cell] & 1) {
                                    vertices[0] = Math::Vector3D<float>(0.0f, 0.0f, 0.5f) * target.getResolution() + cellShift;
                                }
                                if (edgeTable[cell] & 2) {
                                    vertices[1] = Math::Vector3D<float>(0.5f, 0.0f, 1.0f) * target.getResolution() + cellShift;
                                }
                                if (edgeTable[cell] & 4) {
                                    vertices[2] = Math::Vector3D<float>(1.0f, 0.0f, 0.5f) * target.getResolution() + cellShift;
                                }
                                if (edgeTable[cell] & 8) {
                                    vertices[3] = Math::Vector3D<float>(0.5f, 0.0f, 0.0f) * target.getResolution() + cellShift;
                                }
                                if (edgeTable[cell] & 16) {
                                    vertices[4] = Math::Vector3D<float>(0.0f, 1.0f, 0.5f) * target.getResolution() + cellShift;
                                }
                                if (edgeTable[cell] & 32) {
                                    vertices[5] = Math::Vector3D<float>(0.5f, 1.0f, 1.0f) * target.getResolution() + cellShift;
                                }
                                if (edgeTable[cell] & 64) {
                                    vertices[6] = Math::Vector3D<float>(1.0f, 1.0f, 0.5f) * target.getResolution() + cellShift;
                                }
                                if (edgeTable[cell] & 128) {
                                    vertices[7] = Math::Vector3D<float>(0.5f, 1.0f, 0.0f) * target.getResolution() + cellShift;
                                }
                                if (edgeTable[cell] & 256) {
                                    vertices[8] = Math::Vector3D<float>(0.0f, 0.5f, 0.0f) * target.getResolution() + cellShift;
                                }
                                if (edgeTable[cell] & 512) {
                                    vertices[9] = Math::Vector3D<float>(0.0f, 0.5f, 1.0f) * target.getResolution() + cellShift;
                                }
                                if (edgeTable[cell] & 1024) {
                                    vertices[10] = Math::Vector3D<float>(1.0f, 0.5f, 1.0f) * target.getResolution() + cellShift;
                                }
                                if (edgeTable[cell] & 2048) {
                                    vertices[11] = Math::Vector3D<float>(1.0f, 0.5f, 0.0f) * target.getResolution() + cellShift;
                                }

                                for (int i = 0; triTable[cell][i] != 0xFF; i += 3) {
                                    ibo.addData(vertices[triTable[cell][i    ]], Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                                    ibo.addData(vertices[triTable[cell][i + 1]], Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                                    ibo.addData(vertices[triTable[cell][i + 2]], Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                                }
                            }
                        }
                    }
                }
            }

        }
    }
