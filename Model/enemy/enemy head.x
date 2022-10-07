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
 136;
 0.00000;33.47482;-22.09433;,
 16.54102;33.47482;-15.58474;,
 17.01028;24.26897;-16.87962;,
 0.00000;24.26897;-23.92548;,
 22.22499;33.47482;0.13066;,
 22.43369;24.26897;0.13066;,
 15.71541;33.47482;15.84614;,
 17.01028;24.26897;17.14097;,
 0.00000;33.47482;22.35568;,
 0.00000;24.26897;22.60410;,
 -15.71544;33.47482;15.84614;,
 -17.01028;24.26897;17.14097;,
 -22.22499;33.47482;0.13066;,
 -22.43369;24.26897;0.13066;,
 -16.51135;33.47482;-15.58474;,
 -17.01028;24.26897;-16.87962;,
 0.00000;33.47482;-22.09433;,
 0.00000;24.26897;-23.92548;,
 15.71541;15.06307;-15.58474;,
 0.00000;15.06307;-22.09433;,
 20.52033;15.06307;0.13066;,
 15.71541;15.06307;15.84614;,
 0.00000;15.06307;22.35568;,
 -15.71544;15.06307;15.84614;,
 -20.52033;15.06307;0.13066;,
 -15.71544;15.06307;-15.58474;,
 0.00000;15.06307;-22.09433;,
 12.02807;7.25862;-11.89741;,
 0.00000;7.25862;-16.87962;,
 17.01028;7.25862;0.13066;,
 12.02807;7.25862;12.15877;,
 0.00000;7.25862;17.14097;,
 -12.02807;7.25862;12.15877;,
 -17.01028;7.25862;0.13066;,
 -12.02807;7.25862;-11.89741;,
 0.00000;7.25862;-16.87962;,
 6.50954;2.04393;-6.37888;,
 0.00000;2.04393;-9.07521;,
 9.20588;2.04393;0.13066;,
 6.50954;2.04393;6.64023;,
 0.00000;2.04393;9.33656;,
 -6.50954;2.04393;6.64023;,
 -9.20588;2.04393;0.13066;,
 -6.50954;2.04393;-6.37888;,
 0.00000;2.04393;-9.07521;,
 0.00000;0.21277;0.13066;,
 0.00000;0.21277;0.13066;,
 0.00000;0.21277;0.13066;,
 0.00000;0.21277;0.13066;,
 0.00000;0.21277;0.13066;,
 0.00000;0.21277;0.13066;,
 0.00000;0.21277;0.13066;,
 0.00000;0.21277;0.13066;,
 6.59940;27.27882;-21.31476;,
 10.10749;27.27882;-21.31476;,
 10.10749;17.67113;-21.31476;,
 6.59940;17.67113;-21.31476;,
 10.10749;27.27882;-21.31476;,
 10.10749;27.27882;-16.67636;,
 10.10749;17.67113;-16.67636;,
 10.10749;17.67113;-21.31476;,
 10.10749;27.27882;-16.67636;,
 6.59940;27.27882;-16.67636;,
 6.59940;17.67113;-16.67636;,
 10.10749;17.67113;-16.67636;,
 6.59940;27.27882;-16.67636;,
 6.59940;27.27882;-21.31476;,
 6.59940;17.67113;-21.31476;,
 6.59940;17.67113;-16.67636;,
 10.10749;27.27882;-21.31476;,
 6.59940;27.27882;-21.31476;,
 6.59940;17.67113;-21.31476;,
 10.10749;17.67113;-21.31476;,
 -9.89935;27.27882;-21.31476;,
 -6.39122;27.27882;-21.31476;,
 -6.39122;17.67113;-21.31476;,
 -9.89935;17.67113;-21.31476;,
 -6.39122;27.27882;-21.31476;,
 -6.39122;27.27882;-16.67636;,
 -6.39122;17.67113;-16.67636;,
 -6.39122;17.67113;-21.31476;,
 -6.39122;27.27882;-16.67636;,
 -9.89935;27.27882;-16.67636;,
 -9.89935;17.67113;-16.67636;,
 -6.39122;17.67113;-16.67636;,
 -9.89935;27.27882;-16.67636;,
 -9.89935;27.27882;-21.31476;,
 -9.89935;17.67113;-21.31476;,
 -9.89935;17.67113;-16.67636;,
 -6.39122;27.27882;-21.31476;,
 -9.89935;27.27882;-21.31476;,
 -9.89935;17.67113;-21.31476;,
 -6.39122;17.67113;-21.31476;,
 0.00000;50.31661;0.13066;,
 7.03958;48.31502;-6.90893;,
 0.00000;48.31502;-9.82479;,
 0.00000;50.31661;0.13066;,
 9.95545;48.31502;0.13066;,
 0.00000;50.31661;0.13066;,
 7.03958;48.31502;7.17024;,
 0.00000;50.31661;0.13066;,
 0.00000;48.31502;10.08614;,
 0.00000;50.31661;0.13066;,
 -7.03958;48.31502;7.17024;,
 0.00000;50.31661;0.13066;,
 -9.95545;48.31502;0.13066;,
 0.00000;50.31661;0.13066;,
 -7.03958;48.31502;-6.90893;,
 0.00000;50.31661;0.13066;,
 0.00000;48.31502;-9.82479;,
 12.98430;42.63976;-12.85361;,
 0.00000;42.63976;-18.23190;,
 18.36257;42.63976;0.13066;,
 12.98430;42.63976;13.11496;,
 0.00000;42.63976;18.49326;,
 -12.98430;42.63976;13.11496;,
 -18.36257;42.63976;0.13066;,
 -12.98430;42.63976;-12.85361;,
 0.00000;42.63976;-18.23190;,
 16.84793;34.54497;-16.71726;,
 -0.00392;36.67038;-23.69589;,
 23.82656;34.54497;0.13066;,
 16.84793;34.54497;16.97862;,
 0.00000;34.54497;23.95726;,
 -16.84797;34.54497;16.97862;,
 -23.82656;34.54497;0.13066;,
 -16.84797;34.54497;-16.71726;,
 -0.00392;36.67038;-23.69589;,
 13.76961;30.70769;-30.41958;,
 -0.00392;32.66851;-37.09889;,
 13.72020;29.63751;-30.37038;,
 -0.00392;31.59833;-37.02383;,
 -0.00392;32.66851;-37.09889;,
 -13.78278;30.70769;-30.24162;,
 -13.82618;29.63751;-30.07712;,
 -0.00392;31.59833;-37.02383;;
 
 90;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;28,27,36,37;,
 4;27,29,38,36;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 3;37,36,45;,
 3;36,38,46;,
 3;38,39,47;,
 3;39,40,48;,
 3;40,41,49;,
 3;41,42,50;,
 3;42,43,51;,
 3;43,44,52;,
 4;53,54,55,56;,
 4;57,58,59,60;,
 4;61,62,63,64;,
 4;65,66,67,68;,
 4;65,58,69,70;,
 4;71,72,59,68;,
 4;73,74,75,76;,
 4;77,78,79,80;,
 4;81,82,83,84;,
 4;85,86,87,88;,
 4;85,78,89,90;,
 4;91,92,79,88;,
 3;93,94,95;,
 3;96,97,94;,
 3;98,99,97;,
 3;100,101,99;,
 3;102,103,101;,
 3;104,105,103;,
 3;106,107,105;,
 3;108,109,107;,
 4;95,94,110,111;,
 4;94,97,112,110;,
 4;97,99,113,112;,
 4;99,101,114,113;,
 4;101,103,115,114;,
 4;103,105,116,115;,
 4;105,107,117,116;,
 4;107,109,118,117;,
 4;111,110,119,120;,
 4;119,121,4,1;,
 4;110,112,121,119;,
 4;121,122,6,4;,
 4;112,113,122,121;,
 4;122,123,8,6;,
 4;113,114,123,122;,
 4;123,124,10,8;,
 4;114,115,124,123;,
 4;124,125,12,10;,
 4;115,116,125,124;,
 4;125,126,14,12;,
 4;116,117,126,125;,
 4;117,118,127,126;,
 4;128,129,120,119;,
 4;130,128,119,1;,
 4;131,130,1,0;,
 4;129,128,130,131;,
 4;132,133,126,127;,
 4;134,135,16,14;,
 4;133,134,14,126;,
 4;133,132,135,134;;
 
 MeshMaterialList {
  5;
  90;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.000000;0.780800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.796800;0.690400;0.592800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  89;
  -0.000132;0.177176;-0.984179;,
  0.855897;-0.198925;-0.477356;,
  0.915869;-0.401446;-0.005007;,
  0.703305;0.108887;0.702500;,
  0.000000;0.106394;0.994324;,
  -0.703305;0.108886;0.702500;,
  -0.973379;-0.209940;-0.091974;,
  -0.856237;-0.193778;-0.478861;,
  -0.000067;-0.008834;-0.999961;,
  0.732684;-0.040336;-0.679373;,
  0.998351;-0.057143;0.005488;,
  0.714642;-0.024197;0.699071;,
  0.000000;0.000000;1.000000;,
  -0.714643;-0.024197;0.699071;,
  -0.998375;-0.056747;0.005285;,
  -0.732609;-0.039753;-0.679488;,
  0.000000;-0.384549;-0.923105;,
  0.683031;-0.368287;-0.630741;,
  0.942339;-0.334659;-0.000001;,
  0.680530;-0.349465;0.644013;,
  0.000000;-0.341608;0.939842;,
  -0.680530;-0.349465;0.644013;,
  -0.942339;-0.334659;-0.000001;,
  -0.683031;-0.368287;-0.630740;,
  0.000000;-0.709229;-0.704978;,
  0.518298;-0.695510;-0.497628;,
  0.739735;-0.672898;-0.000001;,
  0.518298;-0.695511;0.497627;,
  0.000000;-0.709230;0.704977;,
  -0.518298;-0.695511;0.497626;,
  -0.739735;-0.672898;-0.000001;,
  -0.518298;-0.695510;-0.497627;,
  0.000000;-0.924736;-0.380609;,
  0.269131;-0.924736;-0.269131;,
  0.380609;-0.924736;-0.000000;,
  0.269131;-0.924736;0.269131;,
  0.000000;-0.924736;0.380609;,
  -0.269131;-0.924736;0.269131;,
  -0.380609;-0.924736;-0.000000;,
  -0.269131;-0.924736;-0.269131;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.923453;-0.383712;,
  0.271325;0.923453;-0.271325;,
  0.383711;0.923453;-0.000000;,
  0.271325;0.923453;0.271324;,
  0.000000;0.923454;0.383711;,
  -0.271325;0.923453;0.271324;,
  -0.383711;0.923453;-0.000000;,
  -0.271325;0.923453;-0.271325;,
  -0.000013;0.734466;-0.678645;,
  0.500811;0.718148;-0.483168;,
  0.705090;0.709118;-0.000000;,
  0.498574;0.709118;0.498573;,
  0.000000;0.709119;0.705089;,
  -0.498574;0.709119;0.498573;,
  -0.705089;0.709118;-0.000000;,
  -0.500816;0.718171;-0.483128;,
  -0.000656;0.823944;-0.566671;,
  0.493163;0.723433;-0.483151;,
  0.625334;-0.780116;-0.019419;,
  0.392846;-0.831470;0.392847;,
  0.000000;-0.831470;0.555570;,
  -0.392846;-0.831471;0.392846;,
  -0.621983;-0.782813;-0.018460;,
  -0.857353;-0.467208;-0.216013;,
  0.000780;-0.979865;0.199661;,
  0.790085;-0.153268;-0.593526;,
  0.154095;-0.967934;0.198391;,
  -0.001212;0.952315;-0.305113;,
  0.255211;0.921091;-0.294039;,
  -0.257553;0.919878;-0.295789;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.854440;-0.473639;-0.213539;,
  0.828848;0.559474;-0.000000;,
  0.586084;0.559474;0.586083;,
  0.000000;0.559475;0.828847;,
  -0.586084;0.559475;0.586083;,
  -0.541417;-0.810293;0.224261;,
  -0.828847;0.559475;-0.000000;,
  -0.493807;0.722742;-0.483527;,
  -0.152554;-0.968622;0.196209;,
  -0.003750;-0.085177;-0.996359;,
  -0.792147;-0.156280;-0.589983;;
  90;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  3;32,33,40;,
  3;33,34,40;,
  3;34,35,40;,
  3;35,36,40;,
  3;36,37,40;,
  3;37,38,40;,
  3;38,39,40;,
  3;39,32,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  3;44,46,45;,
  3;44,47,46;,
  3;44,48,47;,
  3;44,49,48;,
  3;44,50,49;,
  3;44,51,50;,
  3;44,52,51;,
  3;44,45,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,45,53,60;,
  4;53,54,62,61;,
  4;78,63,2,1;,
  4;54,55,79,62;,
  4;63,64,64,2;,
  4;55,56,80,79;,
  4;64,65,65,64;,
  4;56,57,81,80;,
  4;65,66,66,65;,
  4;57,58,82,81;,
  4;66,67,83,66;,
  4;58,59,84,82;,
  4;67,68,7,6;,
  4;59,60,85,84;,
  4;60,53,61,85;,
  4;73,72,61,62;,
  4;70,70,78,1;,
  4;69,86,86,69;,
  4;87,70,70,87;,
  4;72,74,85,61;,
  4;71,69,69,71;,
  4;88,88,7,68;,
  4;88,87,87,88;;
 }
 MeshTextureCoords {
  136;
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
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
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.875000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;;
 }
}
