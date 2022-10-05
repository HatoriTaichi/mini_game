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
 -10.00000;-1.07890;-7.15936;,
 -6.73432;-1.07890;-8.65335;,
 -6.73432;-6.74748;-9.91720;,
 -10.00000;-6.74748;-7.15936;,
 6.73432;-1.07890;-8.65335;,
 6.73432;-6.74748;-9.91720;,
 10.00000;-1.07890;-7.15936;,
 10.00000;-6.74748;-7.15936;,
 -6.73432;-12.02143;-8.86224;,
 -10.00000;-12.02143;-6.54749;,
 6.73432;-12.02143;-8.86224;,
 10.00000;-12.02143;-6.54749;,
 10.00000;-1.07890;-7.15936;,
 12.51621;-1.07890;-4.13066;,
 12.51621;-6.74748;-4.13066;,
 10.00000;-6.74748;-7.15936;,
 12.51621;-1.07890;4.13066;,
 12.51621;-6.74748;4.13066;,
 10.00000;-1.07890;7.15936;,
 10.00000;-6.74748;7.15936;,
 12.51621;-12.41607;-4.13066;,
 10.00000;-12.02143;-6.54749;,
 12.51621;-12.41607;4.13066;,
 10.00000;-11.31263;7.15936;,
 10.00000;-1.07890;7.15936;,
 6.73432;-1.07890;8.65335;,
 6.73432;-6.74748;8.65335;,
 10.00000;-6.74748;7.15936;,
 -6.73432;-1.07890;8.65335;,
 -6.73432;-6.74748;8.65335;,
 -10.00000;-1.07890;7.15936;,
 -10.00000;-6.74748;7.15936;,
 6.73432;-11.31263;8.65335;,
 10.00000;-11.31263;7.15936;,
 -6.73432;-11.31263;8.65335;,
 -10.00000;-11.31263;7.15936;,
 -10.00000;-1.07890;7.15936;,
 -12.51621;-1.07890;4.13066;,
 -12.51621;-6.74748;4.13066;,
 -10.00000;-6.74748;7.15936;,
 -12.51621;-1.07890;-4.13066;,
 -12.51621;-6.74748;-4.13066;,
 -10.00000;-1.07890;-7.15936;,
 -10.00000;-6.74748;-7.15936;,
 -12.51621;-12.41607;4.13066;,
 -10.00000;-11.31263;7.15936;,
 -12.51621;-12.41607;-4.13066;,
 -10.00000;-12.02143;-6.54749;,
 -6.73432;-1.07890;8.65335;,
 -6.73432;1.27793;4.13066;,
 -12.51621;-1.07890;4.13066;,
 6.73432;-1.07890;8.65335;,
 6.73432;1.27793;4.13066;,
 12.51621;-1.07890;4.13066;,
 -6.73432;1.27793;-4.13066;,
 -12.51621;-1.07890;-4.13066;,
 6.73432;1.27793;-4.13066;,
 12.51621;-1.07890;-4.13066;,
 -6.73432;-1.07890;-8.65335;,
 -10.00000;-1.07890;-7.15936;,
 6.73432;-1.07890;-8.65335;,
 10.00000;-1.07890;-7.15936;,
 -12.51621;-12.41607;4.13066;,
 -6.73432;-14.54102;4.13066;,
 -6.73432;-11.31263;8.65335;,
 6.73432;-14.54102;4.13066;,
 6.73432;-11.31263;8.65335;,
 12.51621;-12.41607;4.13066;,
 -12.51621;-12.41607;-4.13066;,
 -6.73432;-14.54102;-4.13066;,
 6.73432;-14.54102;-4.13066;,
 12.51621;-12.41607;-4.13066;,
 -10.00000;-12.02143;-6.54749;,
 -6.73432;-12.02143;-8.86224;,
 6.73432;-12.02143;-8.86224;,
 10.00000;-12.02143;-6.54749;;
 
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
  50;
  -0.603898;0.367497;-0.707286;,
  -0.235934;0.597135;-0.766659;,
  0.235934;0.597135;-0.766659;,
  -0.667338;-0.018905;-0.744515;,
  -0.303247;-0.004335;-0.952902;,
  0.303247;-0.004335;-0.952902;,
  -0.607191;-0.366475;-0.704993;,
  -0.262976;-0.583132;-0.768635;,
  0.262976;-0.583132;-0.768635;,
  0.603898;0.367497;-0.707286;,
  0.940527;0.000000;-0.339718;,
  0.940527;0.000000;0.339718;,
  0.667338;-0.018905;-0.744515;,
  0.935664;-0.009903;-0.352754;,
  0.607191;-0.366475;-0.704993;,
  0.930471;-0.019910;-0.365825;,
  0.607818;0.000000;0.794076;,
  0.212888;0.000000;0.977077;,
  -0.212888;0.000000;0.977077;,
  0.607818;0.000000;0.794076;,
  0.546032;-0.295827;0.783795;,
  0.197081;-0.457991;0.866835;,
  -0.197081;-0.457991;0.866835;,
  -0.607818;0.000000;0.794076;,
  -0.940527;0.000000;0.339718;,
  -0.940527;0.000000;-0.339718;,
  -0.607818;0.000000;0.794076;,
  -0.935664;-0.009903;-0.352754;,
  -0.546032;-0.295827;0.783795;,
  -0.930471;-0.019910;-0.365825;,
  -0.172321;0.960513;0.218448;,
  0.172321;0.960513;0.218448;,
  -0.172321;0.960513;-0.218448;,
  0.172321;0.960513;-0.218448;,
  -0.164331;-0.939931;0.299208;,
  0.164331;-0.939931;0.299208;,
  -0.171476;-0.955367;-0.240563;,
  0.171476;-0.955367;-0.240563;,
  -0.285194;0.880821;0.377914;,
  -0.144200;0.893755;0.424744;,
  -0.337871;0.921257;0.192688;,
  0.144200;0.893755;0.424744;,
  0.285194;0.880821;0.377914;,
  0.337871;0.921257;0.192688;,
  -0.337871;0.921257;-0.192688;,
  0.337871;0.921257;-0.192688;,
  -0.323199;-0.902281;0.285362;,
  0.323199;-0.902281;0.285362;,
  -0.337445;-0.912358;-0.231808;,
  0.337445;-0.912358;-0.231808;;
  42;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;2,9,12,5;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;5,12,14,8;,
  4;9,10,13,12;,
  4;10,11,11,13;,
  4;11,16,19,11;,
  4;12,13,15,14;,
  4;13,11,11,15;,
  4;11,19,20,11;,
  4;16,17,17,19;,
  4;17,18,18,17;,
  4;18,23,26,18;,
  4;19,17,21,20;,
  4;17,18,22,21;,
  4;18,26,28,22;,
  4;23,24,24,26;,
  4;24,25,27,24;,
  4;25,0,3,27;,
  4;26,24,24,28;,
  4;24,27,29,24;,
  4;27,3,6,29;,
  4;38,39,30,40;,
  4;39,41,31,30;,
  4;41,42,43,31;,
  4;40,30,32,44;,
  4;30,31,33,32;,
  4;31,43,45,33;,
  4;44,32,1,0;,
  4;32,33,2,1;,
  4;33,45,9,2;,
  4;46,34,22,28;,
  4;34,35,21,22;,
  4;35,47,20,21;,
  4;48,36,34,46;,
  4;36,37,35,34;,
  4;37,49,47,35;,
  4;6,7,36,48;,
  4;7,8,37,36;,
  4;8,14,49,37;;
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
