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
 120;
 -8.56681;3.08022;-10.83296;,
 -0.03794;2.08288;-5.41695;,
 -0.03794;0.17383;-5.41695;,
 -8.70601;1.20019;-10.83296;,
 -0.03794;2.08288;5.41241;,
 -8.56681;3.08022;10.82839;,
 -8.70601;1.20019;10.82839;,
 -0.03794;0.17383;5.41241;,
 -8.56681;3.08022;10.82839;,
 -0.03794;2.08288;5.41241;,
 -0.03794;2.08288;-0.00227;,
 -8.56681;6.18670;-0.00227;,
 -0.03794;2.08288;-5.41695;,
 -8.56681;3.08022;-10.83296;,
 -8.70601;4.30667;-0.00227;,
 -0.03794;0.17383;-0.00227;,
 -0.03794;0.17383;5.41241;,
 -8.70601;1.20019;10.82839;,
 -8.70601;1.20019;-10.83296;,
 -0.03794;0.17383;-5.41695;,
 -29.22214;14.86127;-0.00227;,
 -20.84961;8.23860;10.82839;,
 -8.56681;6.18670;-0.00227;,
 -20.98880;6.35856;10.82839;,
 -29.36133;12.98122;-0.00227;,
 -8.70601;4.30667;-0.00227;,
 -20.84961;8.23860;-10.83296;,
 -8.56681;3.08022;-10.83296;,
 -20.98880;6.35856;-10.83296;,
 -8.70601;1.20019;-10.83296;,
 8.48110;3.02481;10.82839;,
 -0.04782;2.08288;5.41241;,
 -0.04782;0.17383;5.41241;,
 8.62028;1.14479;10.82839;,
 -0.04782;2.08288;-5.41695;,
 8.48110;3.02481;-10.83294;,
 8.62028;1.14479;-10.83294;,
 -0.04782;0.17383;-5.41695;,
 8.48110;3.02481;-10.83294;,
 -0.04782;2.08288;-5.41695;,
 -0.04782;2.08288;-0.00227;,
 8.48110;6.13129;-0.00227;,
 -0.04782;2.08288;5.41241;,
 8.48110;3.02481;10.82839;,
 8.62028;4.25124;-0.00227;,
 -0.04782;0.17383;-0.00227;,
 -0.04782;0.17383;-5.41695;,
 8.62028;1.14479;-10.83294;,
 8.62028;1.14479;10.82839;,
 -0.04782;0.17383;5.41241;,
 29.13648;14.80589;-0.00227;,
 20.76389;8.18320;-10.83296;,
 8.48110;6.13129;-0.00227;,
 20.90306;6.30315;-10.83296;,
 29.27564;12.92583;-0.00227;,
 8.62028;4.25124;-0.00227;,
 20.76389;8.18320;10.82839;,
 8.48110;3.02481;10.82839;,
 20.90306;6.30315;10.82839;,
 8.62028;1.14479;10.82839;,
 -5.29292;5.22978;4.35573;,
 -2.67815;3.46733;0.03161;,
 -2.67815;1.58730;0.17503;,
 -5.29292;3.34973;4.49914;,
 2.55009;3.46733;0.03161;,
 5.16487;5.22978;4.35573;,
 5.16487;3.34973;4.49914;,
 2.55009;1.58730;0.17503;,
 5.16487;5.22978;4.35573;,
 2.55009;3.46733;0.03161;,
 -0.06403;3.46733;0.03161;,
 -0.06403;6.47425;4.35573;,
 -2.67815;3.46733;0.03161;,
 -5.29292;5.22978;4.35573;,
 -0.06403;4.59421;4.49914;,
 -0.06403;1.58730;0.17503;,
 2.55009;1.58730;0.17503;,
 5.16487;3.34973;4.49914;,
 -5.29292;3.34973;4.49914;,
 -2.67815;1.58730;0.17503;,
 -0.06403;10.85446;15.10247;,
 5.16487;7.83449;10.74633;,
 -0.06403;6.47425;4.35573;,
 5.16487;5.95445;10.88975;,
 -0.06403;8.97443;15.24588;,
 -0.06403;4.59421;4.49914;,
 -5.29292;7.83449;10.74633;,
 -5.29292;5.22978;4.35573;,
 -5.29292;5.95445;10.88975;,
 -5.29292;3.34973;4.49914;,
 5.16487;5.25889;-4.30102;,
 2.55009;3.49643;0.02310;,
 2.55009;1.61641;-0.12032;,
 5.16487;3.37884;-4.44442;,
 -2.67815;3.49643;0.02310;,
 -5.29292;5.25889;-4.30100;,
 -5.29292;3.37884;-4.44442;,
 -2.67815;1.61641;-0.12032;,
 -5.29292;5.25889;-4.30100;,
 -2.67815;3.49643;0.02310;,
 -0.06403;3.49643;0.02310;,
 -0.06403;6.50336;-4.30102;,
 2.55009;3.49643;0.02310;,
 5.16487;5.25889;-4.30102;,
 -0.06403;4.62331;-4.44442;,
 -0.06403;1.61641;-0.12032;,
 -2.67815;1.61641;-0.12032;,
 -5.29292;3.37884;-4.44442;,
 5.16487;3.37884;-4.44442;,
 2.55009;1.61641;-0.12032;,
 -0.06403;10.88354;-15.04772;,
 -5.29292;7.86358;-10.69158;,
 -0.06403;6.50336;-4.30102;,
 -5.29292;5.98353;-10.83500;,
 -0.06403;9.00352;-15.19113;,
 -0.06403;4.62331;-4.44442;,
 5.16487;7.86358;-10.69158;,
 5.16487;5.25889;-4.30102;,
 5.16487;5.98353;-10.83500;,
 5.16487;3.37884;-4.44442;;
 
 56;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;11,10,12,13;,
 4;14,15,16,17;,
 4;18,19,15,14;,
 4;20,21,8,22;,
 4;23,24,25,17;,
 4;21,23,17,8;,
 4;21,20,24,23;,
 4;26,20,22,27;,
 4;28,26,27,29;,
 4;24,28,29,25;,
 4;20,26,28,24;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;41,40,42,43;,
 4;44,45,46,47;,
 4;48,49,45,44;,
 4;50,51,38,52;,
 4;53,54,55,47;,
 4;51,53,47,38;,
 4;51,50,54,53;,
 4;56,50,52,57;,
 4;58,56,57,59;,
 4;54,58,59,55;,
 4;50,56,58,54;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;71,70,72,73;,
 4;74,75,76,77;,
 4;78,79,75,74;,
 4;80,81,68,82;,
 4;83,84,85,77;,
 4;81,83,77,68;,
 4;81,80,84,83;,
 4;86,80,82,87;,
 4;88,86,87,89;,
 4;84,88,89,85;,
 4;80,86,88,84;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;101,100,102,103;,
 4;104,105,106,107;,
 4;108,109,105,104;,
 4;110,111,98,112;,
 4;113,114,115,107;,
 4;111,113,107,98;,
 4;111,110,114,113;,
 4;116,110,112,117;,
 4;118,116,117,119;,
 4;114,118,119,115;,
 4;110,116,118,114;;
 
 MeshMaterialList {
  1;
  56;
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
   0.304000;0.571200;0.254400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  104;
  0.276398;-0.010256;-0.960988;,
  0.531231;-0.019712;-0.846998;,
  0.362526;0.931974;0.000000;,
  -0.360225;-0.932865;-0.000000;,
  0.531228;-0.019712;0.846999;,
  0.276397;-0.010256;0.960989;,
  0.374747;0.927127;0.000000;,
  -0.373588;-0.927595;-0.000000;,
  0.374339;0.891352;-0.255659;,
  -0.427631;0.031659;-0.903399;,
  0.374339;0.891352;0.255659;,
  0.387207;0.921993;0.000000;,
  -0.374338;-0.891352;-0.255660;,
  -0.387206;-0.921993;-0.000000;,
  0.367533;0.909279;0.195270;,
  0.359252;0.923556;0.134097;,
  0.359252;0.923556;-0.134096;,
  0.367533;0.909279;-0.195269;,
  -0.356970;-0.924435;-0.134136;,
  -0.366395;-0.909734;-0.195293;,
  -0.366395;-0.909734;0.195292;,
  -0.356970;-0.924435;0.134135;,
  -0.427630;0.031659;0.903399;,
  -0.772641;0.057202;0.632260;,
  -0.374338;-0.891352;0.255659;,
  -0.772642;0.057202;-0.632259;,
  -0.276448;-0.010258;0.960974;,
  -0.531318;-0.019716;0.846943;,
  -0.357281;0.933997;0.000000;,
  0.355048;-0.934848;-0.000000;,
  -0.531319;-0.019716;-0.846942;,
  -0.276449;-0.010258;-0.960974;,
  -0.372108;0.928189;0.000000;,
  0.370985;-0.928639;-0.000000;,
  -0.374339;0.891352;0.255659;,
  0.427632;0.031653;0.903399;,
  -0.374340;0.891352;-0.255659;,
  -0.387208;0.921993;0.000000;,
  0.374339;-0.891352;0.255658;,
  0.387207;-0.921993;-0.000000;,
  -0.364936;0.910299;-0.195390;,
  -0.354044;0.925532;-0.134325;,
  -0.354043;0.925532;0.134325;,
  -0.364936;0.910299;0.195391;,
  0.351829;-0.926372;0.134358;,
  0.363833;-0.910736;0.195410;,
  0.363833;-0.910736;-0.195411;,
  0.351829;-0.926372;-0.134359;,
  0.427631;0.031653;-0.903399;,
  0.772645;0.057190;-0.632258;,
  0.374339;-0.891352;-0.255659;,
  0.772644;0.057190;0.632259;,
  -0.964873;-0.019983;-0.261955;,
  -0.861960;-0.038562;-0.505507;,
  0.000000;0.849183;-0.528099;,
  -0.000000;-0.849184;0.528096;,
  0.861961;-0.038562;-0.505506;,
  0.964873;-0.019983;-0.261955;,
  0.000000;0.890444;-0.455092;,
  -0.000000;-0.890445;0.455091;,
  -0.215230;0.904332;-0.368592;,
  -0.910587;0.031438;0.412121;,
  0.215230;0.904332;-0.368592;,
  0.000000;0.926035;-0.377438;,
  -0.215231;-0.904331;0.368593;,
  -0.000000;-0.926035;0.377439;,
  0.159776;0.879005;-0.449246;,
  0.102688;0.844694;-0.525307;,
  -0.102688;0.844694;-0.525307;,
  -0.159776;0.879005;-0.449246;,
  -0.102689;-0.844695;0.525305;,
  -0.159776;-0.879006;0.449245;,
  0.159776;-0.879006;0.449245;,
  0.102688;-0.844695;0.525305;,
  0.910587;0.031438;0.412121;,
  0.658337;0.057254;0.750543;,
  0.215231;-0.904331;0.368593;,
  -0.658337;0.057254;0.750543;,
  0.964873;-0.019982;0.261956;,
  0.861960;-0.038560;0.505508;,
  0.000001;0.849183;0.528099;,
  -0.000000;-0.849184;-0.528097;,
  -0.861959;-0.038563;0.505508;,
  -0.964873;-0.019983;0.261956;,
  0.000000;0.890445;0.455092;,
  -0.000000;-0.890445;-0.455091;,
  0.215230;0.904332;0.368591;,
  0.910587;0.031438;-0.412120;,
  -0.215230;0.904332;0.368591;,
  0.000000;0.926035;0.377437;,
  0.215231;-0.904332;-0.368592;,
  -0.000000;-0.926035;-0.377438;,
  -0.159775;0.879005;0.449245;,
  -0.102687;0.844693;0.525308;,
  0.102688;0.844694;0.525307;,
  0.159776;0.879005;0.449245;,
  0.102688;-0.844695;-0.525306;,
  0.159776;-0.879006;-0.449245;,
  -0.159777;-0.879006;-0.449245;,
  -0.102688;-0.844695;-0.525306;,
  -0.910587;0.031438;-0.412120;,
  -0.658337;0.057255;-0.750543;,
  -0.215232;-0.904332;-0.368591;,
  0.658337;0.057255;-0.750543;;
  56;
  4;0,1,1,0;,
  4;4,5,5,4;,
  4;14,15,2,6;,
  4;6,2,16,17;,
  4;7,3,18,19;,
  4;20,21,3,7;,
  4;11,10,14,6;,
  4;12,13,7,19;,
  4;22,22,5,5;,
  4;22,23,23,22;,
  4;8,11,6,17;,
  4;9,9,0,0;,
  4;13,24,20,7;,
  4;25,9,9,25;,
  4;26,27,27,26;,
  4;30,31,31,30;,
  4;40,41,28,32;,
  4;32,28,42,43;,
  4;33,29,44,45;,
  4;46,47,29,33;,
  4;37,36,40,32;,
  4;38,39,33,45;,
  4;48,48,31,31;,
  4;48,49,49,48;,
  4;34,37,32,43;,
  4;35,35,26,26;,
  4;39,50,46,33;,
  4;51,35,35,51;,
  4;52,53,53,52;,
  4;56,57,57,56;,
  4;66,67,54,58;,
  4;58,54,68,69;,
  4;59,55,70,71;,
  4;72,73,55,59;,
  4;63,62,66,58;,
  4;64,65,59,71;,
  4;74,74,57,57;,
  4;74,75,75,74;,
  4;60,63,58,69;,
  4;61,61,52,52;,
  4;65,76,72,59;,
  4;77,61,61,77;,
  4;78,79,79,78;,
  4;82,83,83,82;,
  4;92,93,80,84;,
  4;84,80,94,95;,
  4;85,81,96,97;,
  4;98,99,81,85;,
  4;89,88,92,84;,
  4;90,91,85,97;,
  4;100,100,83,83;,
  4;100,101,101,100;,
  4;86,89,84,95;,
  4;87,87,78,78;,
  4;91,102,98,85;,
  4;103,87,87,103;;
 }
 MeshTextureCoords {
  120;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;;
 }
}