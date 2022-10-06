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
 76;
 -3.56666;-25.21789;-2.56352;,
 -4.23261;-25.21789;-1.40046;,
 -3.92371;-12.33044;-2.06733;,
 -3.25776;-12.33044;-3.23040;,
 -4.23261;-25.21789;1.26206;,
 -3.92371;-12.33044;2.02614;,
 -3.56666;-25.21789;2.42512;,
 -3.25776;-12.33044;3.18920;,
 -4.02119;-1.69478;-2.55793;,
 -3.33842;-1.69478;-3.75036;,
 -4.02119;-1.69478;2.35995;,
 -3.33842;-1.69478;3.55238;,
 -3.56666;-25.21789;2.42512;,
 -2.21661;-25.21789;3.32126;,
 -1.90771;-12.33044;4.08534;,
 -3.25776;-12.33044;3.18920;,
 1.07432;-25.21789;3.32126;,
 1.38322;-12.33044;4.08534;,
 2.42438;-25.21789;2.42512;,
 2.73327;-12.33044;3.18920;,
 -1.95429;-1.69478;4.47115;,
 -3.33842;-1.69478;3.55238;,
 1.82123;-1.69478;4.47115;,
 3.20538;-1.69478;3.55238;,
 2.42438;-25.21789;2.42512;,
 3.09033;-25.21789;1.26206;,
 3.39923;-12.33044;2.02614;,
 2.73327;-12.33044;3.18920;,
 3.09033;-25.21789;-1.40046;,
 3.39923;-12.33044;-2.06733;,
 2.42438;-25.21789;-2.56352;,
 2.73327;-12.33044;-3.23040;,
 3.88815;-1.69478;2.35995;,
 3.20538;-1.69478;3.55238;,
 3.88815;-1.69478;-2.55793;,
 3.20538;-1.69478;-3.75036;,
 2.42438;-25.21789;-2.56352;,
 1.07432;-25.21789;-3.45964;,
 1.38322;-12.33044;-4.12652;,
 2.73327;-12.33044;-3.23040;,
 -2.21661;-25.21789;-3.45964;,
 -1.90771;-12.33044;-4.12652;,
 -3.56666;-25.21789;-2.56352;,
 -3.25776;-12.33044;-3.23040;,
 1.82123;-1.69478;-4.66911;,
 3.20538;-1.69478;-3.75036;,
 -1.95429;-1.69478;-4.66911;,
 -3.33842;-1.69478;-3.75036;,
 3.09033;-25.21789;-1.40046;,
 1.46591;-28.78641;-2.33443;,
 1.07432;-25.21789;-3.45964;,
 3.09033;-25.21789;1.26206;,
 1.46591;-28.75726;2.46233;,
 1.07432;-25.21789;3.32126;,
 -2.21661;-28.78641;-2.33443;,
 -2.21661;-25.21789;-3.45964;,
 -2.21661;-28.75726;2.46233;,
 -2.21661;-25.21789;3.32126;,
 -4.23261;-25.21789;-1.40046;,
 -3.56666;-25.21789;-2.56352;,
 -4.23261;-25.21789;1.26206;,
 -3.56666;-25.21789;2.42512;,
 1.82123;-1.69478;-4.66911;,
 1.51241;1.65072;-2.55793;,
 3.88815;-1.69478;-2.55793;,
 1.82123;1.65072;2.35995;,
 3.88815;-1.69478;2.35995;,
 1.82123;-1.69478;4.47115;,
 -1.95429;-1.69478;-4.66911;,
 -1.95429;1.65072;-2.55793;,
 -1.95429;1.65072;2.35995;,
 -1.95429;-1.69478;4.47115;,
 -3.33842;-1.69478;-3.75036;,
 -4.02119;-1.69478;-2.55793;,
 -4.02119;-1.69478;2.35995;,
 -3.33842;-1.69478;3.55238;;
 
 42;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;2,5,10,8;,
 4;5,7,11,10;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;16,18,19,17;,
 4;15,14,20,21;,
 4;14,17,22,20;,
 4;17,19,23,22;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;28,30,31,29;,
 4;27,26,32,33;,
 4;26,29,34,32;,
 4;29,31,35,34;,
 4;36,37,38,39;,
 4;37,40,41,38;,
 4;40,42,43,41;,
 4;39,38,44,45;,
 4;38,41,46,44;,
 4;41,43,47,46;,
 4;36,48,49,50;,
 4;48,51,52,49;,
 4;51,18,53,52;,
 4;50,49,54,55;,
 4;49,52,56,54;,
 4;52,53,57,56;,
 4;55,54,58,59;,
 4;54,56,60,58;,
 4;56,57,61,60;,
 4;62,63,64,45;,
 4;63,65,66,64;,
 4;65,67,23,66;,
 4;68,69,63,62;,
 4;69,70,65,63;,
 4;70,71,67,65;,
 4;72,73,69,68;,
 4;73,74,70,69;,
 4;74,75,71,70;;
 
 MeshMaterialList {
  5;
  42;
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
  49;
  -0.724396;-0.116166;-0.679526;,
  -0.927061;-0.210281;-0.310385;,
  -0.928496;-0.199381;0.313277;,
  -0.729790;-0.028390;-0.683082;,
  -0.966376;-0.005427;-0.257075;,
  -0.966378;-0.004503;0.257087;,
  -0.722631;0.141416;-0.676614;,
  -0.917033;0.263352;-0.299493;,
  -0.916550;0.265196;0.299346;,
  -0.725275;-0.104453;0.680489;,
  -0.336252;-0.158631;0.928316;,
  0.339164;-0.145616;0.929389;,
  -0.729836;-0.025935;0.683130;,
  -0.288649;-0.042872;0.956475;,
  0.288318;-0.055065;0.955950;,
  -0.721904;0.148099;0.675960;,
  -0.330202;0.261151;0.907065;,
  0.330622;0.255964;0.908390;,
  0.725855;-0.101853;0.680264;,
  0.932579;-0.180618;0.312528;,
  0.931089;-0.192067;-0.310135;,
  0.728889;-0.056786;0.682273;,
  0.965416;-0.045397;0.256732;,
  0.965379;-0.046317;-0.256705;,
  0.723710;0.130254;0.677700;,
  0.920417;0.256352;0.295154;,
  0.914534;0.266217;-0.304561;,
  0.724902;-0.114420;-0.679283;,
  0.338170;-0.172119;-0.925211;,
  -0.334868;-0.184480;-0.924029;,
  0.728787;-0.059232;-0.682173;,
  0.288250;-0.058498;-0.955767;,
  -0.288600;-0.046310;-0.956329;,
  0.722455;0.139832;-0.677131;,
  0.326798;0.261889;-0.908084;,
  -0.330858;0.254253;-0.908784;,
  0.867406;-0.347545;-0.356117;,
  0.873999;-0.323753;0.362367;,
  -0.374403;-0.326689;-0.867811;,
  0.000000;-0.999982;0.006076;,
  0.437782;0.785166;-0.438019;,
  0.449102;0.781646;0.432825;,
  -0.454686;0.773891;-0.440856;,
  -0.250254;0.786298;0.564896;,
  0.000000;-0.300722;-0.953712;,
  0.000000;-0.235832;0.971794;,
  -0.380345;-0.269014;0.884856;,
  -0.870017;-0.493020;0.001501;,
  -0.850734;0.525596;0.000000;;
  42;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;2,9,12,5;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;5,12,15,8;,
  4;9,10,13,12;,
  4;10,11,14,13;,
  4;11,18,21,14;,
  4;12,13,16,15;,
  4;13,14,17,16;,
  4;14,21,24,17;,
  4;18,19,22,21;,
  4;19,20,23,22;,
  4;20,27,30,23;,
  4;21,22,25,24;,
  4;22,23,26,25;,
  4;23,30,33,26;,
  4;27,28,31,30;,
  4;28,29,32,31;,
  4;29,0,3,32;,
  4;30,31,34,33;,
  4;31,32,35,34;,
  4;32,3,6,35;,
  4;27,20,36,28;,
  4;20,19,37,36;,
  4;19,18,11,37;,
  4;28,44,38,29;,
  4;39,39,39,39;,
  4;45,11,10,46;,
  4;29,38,1,0;,
  4;47,47,2,1;,
  4;46,10,9,2;,
  4;34,40,26,33;,
  4;40,41,25,26;,
  4;41,17,24,25;,
  4;35,42,40,34;,
  4;42,43,41,40;,
  4;43,16,17,41;,
  4;6,7,42,35;,
  4;7,8,48,42;,
  4;8,15,16,43;;
 }
 MeshTextureCoords {
  76;
  0.000000;0.000000;,
  0.333333;0.000000;,
  0.333333;0.500000;,
  0.000000;0.500000;,
  0.666667;0.000000;,
  0.666667;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.333333;1.000000;,
  0.000000;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333333;0.000000;,
  0.333333;0.500000;,
  0.000000;0.500000;,
  0.666667;0.000000;,
  0.666667;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.333333;1.000000;,
  0.000000;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333333;0.000000;,
  0.333333;0.500000;,
  0.000000;0.500000;,
  0.666667;0.000000;,
  0.666667;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.333333;1.000000;,
  0.000000;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333333;0.000000;,
  0.333333;0.500000;,
  0.000000;0.500000;,
  0.666667;0.000000;,
  0.666667;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.333333;1.000000;,
  0.000000;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.333333;0.000000;,
  0.333333;0.333333;,
  0.000000;0.333333;,
  0.666667;0.000000;,
  0.666667;0.333333;,
  1.000000;0.333333;,
  0.333333;0.666667;,
  0.000000;0.666667;,
  0.666667;0.666667;,
  1.000000;0.666667;,
  0.333333;1.000000;,
  0.000000;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666667;,
  0.333333;0.666667;,
  0.333333;1.000000;,
  0.666667;0.666667;,
  0.666667;1.000000;,
  1.000000;0.666667;,
  0.000000;0.333333;,
  0.333333;0.333333;,
  0.666667;0.333333;,
  1.000000;0.333333;,
  0.000000;0.000000;,
  0.333333;0.000000;,
  0.666667;0.000000;,
  1.000000;0.000000;;
 }
}
