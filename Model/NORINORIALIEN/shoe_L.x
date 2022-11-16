xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 45;
 0.00486;0.55068;-0.00123;,
 1.68128;-1.03240;-2.70721;,
 0.00486;-1.03240;-3.82806;,
 0.00486;0.55068;-0.00123;,
 2.37567;-0.51894;-0.00123;,
 0.00486;0.55068;-0.00123;,
 1.68128;-0.21052;2.19875;,
 0.00486;0.55068;-0.00123;,
 0.00486;-0.21052;2.61794;,
 0.00486;0.55068;-0.00123;,
 -1.67156;-0.21052;2.19875;,
 0.00486;0.55068;-0.00123;,
 -2.36596;-0.51894;-0.00123;,
 0.00486;0.55068;-0.00123;,
 -1.67156;-1.03240;-2.70721;,
 0.00486;0.55068;-0.00123;,
 0.00486;-1.03240;-3.82806;,
 3.10248;-2.55813;-7.71663;,
 0.00486;-2.55813;-9.78769;,
 3.84174;-2.37825;-2.71663;,
 3.10248;-2.37825;2.28337;,
 0.00486;-2.37825;4.09979;,
 -3.09276;-2.37825;2.28337;,
 -3.37777;-1.90093;-2.71663;,
 -3.09276;-2.55813;-7.71663;,
 0.00486;-2.55813;-9.78769;,
 4.05209;-3.73858;-9.94632;,
 0.00486;-3.84467;-14.81159;,
 4.98176;-3.73858;-3.41351;,
 4.05209;-3.73858;3.11931;,
 0.00486;-3.73858;4.82663;,
 -3.55329;-3.73858;2.65405;,
 -3.86012;-3.73858;-3.41351;,
 -3.69750;-3.73858;-9.94632;,
 0.00486;-3.84467;-14.81159;,
 4.38555;-5.12556;-10.38260;,
 0.00486;-5.23166;-14.63277;,
 5.45335;-5.12556;-4.63277;,
 4.38555;-5.12556;2.43829;,
 0.00486;-5.12556;4.89512;,
 -3.49790;-5.12556;2.78916;,
 -3.95666;-5.12556;-3.39677;,
 -3.67113;-5.12556;-10.38259;,
 0.00486;-5.23166;-14.63277;,
 -0.21125;-5.25664;-4.52129;;
 
 40;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 3;35,37,44;,
 3;35,44,36;,
 3;42,36,44;,
 3;41,42,44;,
 3;40,41,44;,
 3;39,40,44;,
 3;44,38,39;,
 3;37,38,44;;
 
 MeshMaterialList {
  5;
  40;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.796863;0.288627;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.078431;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.713726;0.984314;1.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.542745;0.800000;0.213333;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  43;
  0.000000;0.995200;-0.097864;,
  -0.000000;0.948985;-0.315321;,
  0.335417;0.901511;-0.273447;,
  0.565809;0.820591;-0.080560;,
  0.472222;0.806205;0.356428;,
  0.000000;0.788994;0.614402;,
  -0.477322;0.804688;0.353045;,
  -0.551217;0.829697;-0.088105;,
  -0.315275;0.908181;-0.275333;,
  -0.005155;0.958471;-0.285142;,
  0.422714;0.878668;-0.221935;,
  0.730041;0.683316;-0.010892;,
  0.638127;0.584622;0.501010;,
  -0.028184;0.505755;0.862217;,
  -0.732807;0.455770;0.505240;,
  -0.840527;0.541499;-0.017127;,
  -0.486845;0.844376;-0.223630;,
  -0.010422;0.946446;-0.322693;,
  0.728001;0.591077;-0.347336;,
  0.877777;0.479062;-0.002526;,
  0.750654;0.358673;0.554862;,
  -0.054853;0.258318;0.964501;,
  -0.837987;0.212268;0.502713;,
  -0.983188;0.182385;0.008775;,
  -0.865153;0.400158;-0.302298;,
  0.725218;0.146084;-0.672843;,
  0.863530;0.260324;-0.431912;,
  0.962463;0.271371;-0.004765;,
  0.805483;0.032016;0.591753;,
  -0.047231;-0.043143;0.997952;,
  -0.855033;0.040034;0.517026;,
  -0.999576;0.025133;0.014707;,
  -0.935939;0.040463;-0.349830;,
  -0.003825;-0.999989;0.002887;,
  -0.775086;0.045191;-0.630238;,
  0.024558;-0.999694;-0.003097;,
  0.023126;-0.999733;-0.000388;,
  -0.003221;-0.999992;-0.002540;,
  -0.033957;-0.999421;-0.002306;,
  -0.034812;-0.999394;0.000545;,
  -0.021352;-0.999737;0.008326;,
  -0.000389;-0.999903;0.013928;,
  0.015455;-0.999843;0.008623;;
  40;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;25,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,34,34,32;,
  3;35,36,33;,
  3;35,33,37;,
  3;38,37,33;,
  3;39,38,33;,
  3;40,39,33;,
  3;41,40,33;,
  3;33,42,41;,
  3;36,42,33;;
 }
 MeshTextureCoords {
  45;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;;
 }
}