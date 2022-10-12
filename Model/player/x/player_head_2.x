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
 145;
 0.00000;48.56454;-32.24694;,
 24.04452;48.56454;-22.78441;,
 24.72669;35.18260;-24.66663;,
 0.00000;35.18260;-34.90880;,
 32.30696;48.56454;0.06005;,
 32.61036;35.18260;0.06005;,
 22.84447;48.56454;22.90454;,
 24.72669;35.18260;24.78675;,
 0.00000;48.56454;32.36702;,
 0.00000;35.18260;32.72814;,
 -22.84451;48.56454;22.90454;,
 -24.72669;35.18260;24.78675;,
 -32.30696;48.56454;0.06005;,
 -32.61036;35.18260;0.06005;,
 -24.00148;48.56454;-22.78441;,
 -24.72669;35.18260;-24.66663;,
 0.00000;48.56454;-32.24694;,
 0.00000;35.18260;-34.90880;,
 22.84447;21.80050;-22.78441;,
 0.00000;21.80050;-32.24694;,
 29.82904;21.80050;0.06005;,
 22.84447;21.80050;22.90454;,
 0.00000;21.80050;32.36702;,
 -22.84451;21.80050;22.90454;,
 -29.82904;21.80050;0.06005;,
 -22.84451;21.80050;-22.78441;,
 0.00000;21.80050;-32.24694;,
 17.48440;10.45582;-17.42436;,
 0.00000;10.45582;-24.66663;,
 24.72669;10.45582;0.06005;,
 17.48440;10.45582;17.54448;,
 0.00000;10.45582;24.78675;,
 -17.48440;10.45582;17.54448;,
 -24.72669;10.45582;0.06005;,
 -17.48440;10.45582;-17.42436;,
 0.00000;10.45582;-24.66663;,
 9.46249;2.87550;-9.40244;,
 0.00000;2.87550;-13.32192;,
 13.38198;2.87550;0.06005;,
 9.46249;2.87550;9.52255;,
 0.00000;2.87550;13.44202;,
 -9.46249;2.87550;9.52255;,
 -13.38198;2.87550;0.06005;,
 -9.46249;2.87550;-9.40244;,
 0.00000;2.87550;-13.32192;,
 0.00000;0.21370;0.06005;,
 0.00000;0.21370;0.06005;,
 0.00000;0.21370;0.06005;,
 0.00000;0.21370;0.06005;,
 0.00000;0.21370;0.06005;,
 0.00000;0.21370;0.06005;,
 0.00000;0.21370;0.06005;,
 0.00000;0.21370;0.06005;,
 9.59309;39.55780;-31.11381;,
 14.69261;39.55780;-31.11381;,
 14.69261;25.59176;-31.11381;,
 9.59309;25.59176;-31.11381;,
 14.69261;39.55780;-31.11381;,
 14.69261;39.55780;-24.37120;,
 14.69261;25.59176;-24.37120;,
 14.69261;25.59176;-31.11381;,
 14.69261;39.55780;-24.37120;,
 9.59309;39.55780;-24.37120;,
 9.59309;25.59176;-24.37120;,
 14.69261;25.59176;-24.37120;,
 9.59309;39.55780;-24.37120;,
 9.59309;39.55780;-31.11381;,
 9.59309;25.59176;-31.11381;,
 9.59309;25.59176;-24.37120;,
 14.69261;39.55780;-31.11381;,
 9.59309;39.55780;-31.11381;,
 9.59309;25.59176;-31.11381;,
 14.69261;25.59176;-31.11381;,
 -14.39002;39.55780;-31.11381;,
 -9.29052;39.55780;-31.11381;,
 -9.29052;25.59176;-31.11381;,
 -14.39002;25.59176;-31.11381;,
 -9.29052;39.55780;-31.11381;,
 -9.29052;39.55780;-24.37120;,
 -9.29052;25.59176;-24.37120;,
 -9.29052;25.59176;-31.11381;,
 -9.29052;39.55780;-24.37120;,
 -14.39002;39.55780;-24.37120;,
 -14.39002;25.59176;-24.37120;,
 -9.29052;25.59176;-24.37120;,
 -14.39002;39.55780;-24.37120;,
 -14.39002;39.55780;-31.11381;,
 -14.39002;25.59176;-31.11381;,
 -14.39002;25.59176;-24.37120;,
 -9.29052;39.55780;-31.11381;,
 -14.39002;39.55780;-31.11381;,
 -14.39002;25.59176;-31.11381;,
 -9.29052;25.59176;-31.11381;,
 0.00000;73.04657;0.06005;,
 10.23296;70.13702;-10.17290;,
 0.00000;70.13702;-14.41154;,
 0.00000;73.04657;0.06005;,
 14.47160;70.13702;0.06005;,
 0.00000;73.04657;0.06005;,
 10.23296;70.13702;10.29303;,
 0.00000;73.04657;0.06005;,
 0.00000;70.13702;14.53166;,
 0.00000;73.04657;0.06005;,
 -10.23296;70.13702;10.29303;,
 0.00000;73.04657;0.06005;,
 -14.47160;70.13702;0.06005;,
 0.00000;73.04657;0.06005;,
 -10.23296;70.13702;-10.17290;,
 0.00000;73.04657;0.06005;,
 0.00000;70.13702;-14.41154;,
 18.87438;61.88682;-18.81433;,
 0.00000;61.88682;-26.63239;,
 26.69242;61.88682;0.06005;,
 18.87438;61.88682;18.93445;,
 0.00000;61.88682;26.75250;,
 -18.87438;61.88682;18.93445;,
 -26.69242;61.88682;0.06005;,
 -18.87438;61.88682;-18.81433;,
 0.00000;61.88682;-26.63239;,
 24.49070;50.12025;-24.43064;,
 -0.00570;53.20977;-34.57506;,
 34.63508;50.12025;0.06005;,
 24.49070;50.12025;24.55075;,
 0.00000;50.12025;34.69513;,
 -24.49074;50.12025;24.55075;,
 -34.63508;50.12025;0.06005;,
 -24.49074;50.12025;-24.43064;,
 -0.00570;53.20977;-34.57506;,
 20.01594;44.54212;-44.34884;,
 -0.00570;47.39239;-54.05808;,
 19.94414;42.98661;-44.27733;,
 -0.00570;45.83688;-53.94901;,
 -0.00570;47.39239;-54.05808;,
 -20.03511;44.54212;-44.09015;,
 -20.09819;42.98661;-43.85104;,
 -0.00570;45.83688;-53.94901;,
 -0.31378;69.82747;-14.94681;,
 9.83307;69.82747;-10.87277;,
 11.18632;63.06885;-20.99811;,
 -0.31374;63.06885;-28.45557;,
 -10.46057;69.82747;-10.62939;,
 -11.81383;63.06885;-21.56429;,
 13.28532;52.95344;-27.75927;,
 -0.31374;52.95344;-35.01386;,
 -13.91287;52.95344;-27.77177;;
 
 94;
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
 4;133,132,135,134;,
 4;136,137,138,139;,
 4;140,136,139,141;,
 4;139,138,142,143;,
 4;141,139,143,144;;
 
 MeshMaterialList {
  5;
  94;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
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
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  4,
  4,
  4,
  4;;
  Material {
   0.000000;0.800000;0.044000;1.000000;;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\Texture\\Player\\pizza_logo.png";
   }
  }
 }
 MeshNormals {
  98;
  -0.000132;0.177175;-0.984179;,
  0.855899;-0.198916;-0.477356;,
  0.915876;-0.401430;-0.005006;,
  0.703305;0.108886;0.702500;,
  0.000000;0.106394;0.994324;,
  -0.703305;0.108885;0.702500;,
  -0.973381;-0.209926;-0.091977;,
  -0.856240;-0.193762;-0.478862;,
  -0.000067;-0.008833;-0.999961;,
  0.732684;-0.040334;-0.679373;,
  0.998351;-0.057141;0.005488;,
  0.714642;-0.024196;0.699071;,
  0.000000;0.000001;1.000000;,
  -0.714643;-0.024196;0.699071;,
  -0.998375;-0.056746;0.005286;,
  -0.732610;-0.039751;-0.679487;,
  0.000000;-0.384551;-0.923104;,
  0.683031;-0.368289;-0.630740;,
  0.942339;-0.334660;-0.000000;,
  0.680530;-0.349467;0.644013;,
  0.000000;-0.341610;0.939842;,
  -0.680530;-0.349467;0.644013;,
  -0.942339;-0.334660;-0.000000;,
  -0.683031;-0.368289;-0.630740;,
  0.000000;-0.709230;-0.704977;,
  0.518298;-0.695511;-0.497627;,
  0.739735;-0.672898;-0.000000;,
  0.518297;-0.695511;0.497627;,
  0.000000;-0.709230;0.704977;,
  -0.518297;-0.695511;0.497627;,
  -0.739735;-0.672898;-0.000000;,
  -0.518297;-0.695511;-0.497627;,
  0.000000;-0.924736;-0.380610;,
  0.269132;-0.924736;-0.269132;,
  0.380610;-0.924736;-0.000000;,
  0.269132;-0.924736;0.269132;,
  0.000000;-0.924736;0.380610;,
  -0.269132;-0.924736;0.269132;,
  -0.380610;-0.924736;-0.000000;,
  -0.269132;-0.924736;-0.269132;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.923449;-0.383722;,
  0.271332;0.923449;-0.271332;,
  0.383722;0.923449;-0.000000;,
  0.271332;0.923449;0.271332;,
  0.000000;0.923449;0.383722;,
  -0.271332;0.923449;0.271332;,
  -0.383722;0.923449;-0.000000;,
  -0.271332;0.923449;-0.271332;,
  -0.000013;0.734461;-0.678650;,
  0.500815;0.718143;-0.483172;,
  0.705095;0.709112;-0.000000;,
  0.498578;0.709112;0.498578;,
  0.000000;0.709112;0.705096;,
  -0.498578;0.709112;0.498578;,
  -0.705095;0.709113;-0.000000;,
  -0.500820;0.718166;-0.483132;,
  -0.000656;0.823946;-0.566668;,
  0.493159;0.723437;-0.483149;,
  0.625359;-0.780096;-0.019417;,
  0.392868;-0.831450;0.392868;,
  0.000000;-0.831450;0.555600;,
  -0.392868;-0.831450;0.392868;,
  -0.622017;-0.782786;-0.018460;,
  -0.857367;-0.467178;-0.216022;,
  0.000780;-0.979866;0.199657;,
  0.790087;-0.153255;-0.593528;,
  0.154092;-0.967935;0.198387;,
  -0.001212;0.952314;-0.305118;,
  0.255211;0.921089;-0.294045;,
  -0.257553;0.919876;-0.295795;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.854447;-0.473623;-0.213543;,
  0.828841;0.559484;-0.000000;,
  0.586079;0.559483;0.586080;,
  0.000000;0.559483;0.828842;,
  -0.586079;0.559484;0.586079;,
  -0.541446;-0.810270;0.224273;,
  -0.828841;0.559485;-0.000000;,
  -0.493803;0.722746;-0.483525;,
  -0.152551;-0.968624;0.196205;,
  -0.003749;-0.085167;-0.996360;,
  -0.792148;-0.156268;-0.589985;,
  0.005059;0.874598;-0.484823;,
  0.244811;0.843933;-0.477331;,
  -0.234989;0.854118;-0.463963;,
  0.005182;0.749949;-0.661476;,
  0.346356;0.703852;-0.620185;,
  -0.337956;0.705518;-0.622920;,
  0.005044;0.577178;-0.816603;,
  0.430465;0.528338;-0.731819;,
  -0.421338;0.516032;-0.745778;;
  94;
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
  4;88,87,87,88;,
  4;89,90,93,92;,
  4;91,89,92,94;,
  4;92,93,96,95;,
  4;94,92,95,97;;
 }
 MeshTextureCoords {
  145;
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
  1.000000;0.375000;,
  0.497301;-1.031617;,
  0.919910;-1.031617;,
  0.976273;-0.612687;,
  0.497303;-0.612687;,
  0.074694;-1.031617;,
  0.018331;-0.612687;,
  1.063695;0.014311;,
  0.497303;0.014311;,
  -0.069092;0.014311;;
 }
}
