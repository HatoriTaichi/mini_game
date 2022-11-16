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
 0.63603;-19.07222;-2.69655;,
 0.19140;-19.07222;-1.82998;,
 0.19140;-10.70794;-1.82998;,
 0.63603;-10.70794;-2.69655;,
 0.19140;-19.07222;1.74399;,
 0.19140;-10.70794;1.74399;,
 0.63603;-19.07222;2.61056;,
 0.63603;-10.70794;2.61056;,
 0.19140;-2.34366;-1.82998;,
 0.63603;-2.34366;-2.69655;,
 0.19140;-2.34366;1.74399;,
 0.63603;-2.34366;2.61056;,
 0.63603;-19.07222;2.61056;,
 1.53739;-19.07222;3.27825;,
 1.53739;-10.70794;3.27825;,
 0.63603;-10.70794;2.61056;,
 3.99604;-19.07222;3.27825;,
 3.99604;-10.70794;3.27825;,
 4.89741;-19.07222;2.61056;,
 4.89741;-10.70794;2.61056;,
 1.53739;-2.34366;3.27825;,
 0.63603;-2.34366;2.61056;,
 3.99604;-2.34366;3.27825;,
 4.89741;-2.34366;2.61056;,
 4.89741;-19.07222;2.61056;,
 5.34203;-19.07222;1.74399;,
 5.34203;-10.70794;1.74399;,
 4.89741;-10.70794;2.61056;,
 5.34203;-19.07222;-1.82998;,
 5.34203;-10.70794;-1.82998;,
 4.89741;-19.07222;-2.69655;,
 4.89741;-10.70794;-2.69655;,
 5.34203;-2.34366;1.74399;,
 4.89741;-2.34366;2.61056;,
 5.34203;-2.34366;-1.82998;,
 4.89741;-2.34366;-2.69655;,
 4.89741;-19.07222;-2.69655;,
 3.99604;-19.07222;-3.36423;,
 3.99604;-10.70794;-3.36423;,
 4.89741;-10.70794;-2.69655;,
 1.53739;-19.07222;-3.36423;,
 1.53739;-10.70794;-3.36423;,
 0.63603;-19.07222;-2.69655;,
 0.63603;-10.70794;-2.69655;,
 3.99604;-2.34366;-3.36423;,
 4.89741;-2.34366;-2.69655;,
 1.53739;-2.34366;-3.36423;,
 0.63603;-2.34366;-2.69655;,
 5.34203;-19.07222;-1.82998;,
 3.99604;-22.54983;-1.82998;,
 3.99604;-19.07222;-3.36423;,
 5.34203;-19.07222;1.74399;,
 3.99604;-22.54983;1.74399;,
 3.99604;-19.07222;3.27825;,
 1.53739;-22.54983;-1.82998;,
 1.53739;-19.07222;-3.36423;,
 1.53739;-22.54983;1.74399;,
 1.53739;-19.07222;3.27825;,
 0.19140;-19.07222;-1.82998;,
 0.63603;-19.07222;-2.69655;,
 0.19140;-19.07222;1.74399;,
 0.63603;-19.07222;2.61056;,
 3.99604;-2.34366;-3.36423;,
 3.99604;0.79181;-1.82998;,
 5.34203;-2.34366;-1.82998;,
 3.99604;0.79181;1.74399;,
 5.34203;-2.34366;1.74399;,
 3.99604;-2.34366;3.27825;,
 1.53739;-2.34366;-3.36423;,
 1.53739;0.79181;-1.82998;,
 1.53739;0.79181;1.74399;,
 1.53739;-2.34366;3.27825;,
 0.63603;-2.34366;-2.69655;,
 0.19140;-2.34366;-1.82998;,
 0.19140;-2.34366;1.74399;,
 0.63603;-2.34366;2.61056;;
 
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
  52;
  -0.757402;-0.116130;-0.642538;,
  -0.940933;-0.185706;-0.283121;,
  -0.940934;-0.185706;0.283120;,
  -0.762484;0.000000;-0.647007;,
  -0.972039;0.000000;-0.234818;,
  -0.972039;0.000000;0.234819;,
  -0.756353;0.127500;-0.641618;,
  -0.937583;0.203721;-0.281844;,
  -0.937583;0.203721;0.281844;,
  -0.757404;-0.116130;0.642537;,
  -0.359472;-0.202959;0.910817;,
  0.359471;-0.202959;0.910817;,
  -0.762485;0.000000;0.647005;,
  -0.313408;0.000000;0.949619;,
  0.313406;0.000000;0.949619;,
  -0.756354;0.127500;0.641617;,
  -0.358051;0.222231;0.906870;,
  0.358051;0.222232;0.906870;,
  0.757404;-0.116131;0.642536;,
  0.940934;-0.185707;0.283119;,
  0.940934;-0.185707;-0.283119;,
  0.762486;0.000000;0.647005;,
  0.972040;0.000000;0.234816;,
  0.972040;0.000000;-0.234816;,
  0.756355;0.127500;0.641616;,
  0.937583;0.203721;0.281842;,
  0.937583;0.203722;-0.281842;,
  0.757403;-0.116131;-0.642537;,
  0.359469;-0.202959;-0.910818;,
  -0.359470;-0.202958;-0.910818;,
  0.762485;0.000000;-0.647006;,
  0.313404;0.000000;-0.949620;,
  -0.313405;0.000000;-0.949619;,
  0.756353;0.127501;-0.641618;,
  0.358049;0.222231;-0.906871;,
  -0.358049;0.222231;-0.906870;,
  0.871963;-0.369134;-0.321590;,
  0.871964;-0.369133;0.321589;,
  -0.659627;-0.440563;-0.608931;,
  0.000000;-1.000000;-0.000000;,
  0.858518;0.403124;-0.316920;,
  0.858518;0.403124;0.316919;,
  -0.646132;0.477880;-0.595100;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.403644;-0.914916;,
  0.000000;-0.403645;0.914916;,
  -0.390111;-0.402881;0.827949;,
  -0.932584;-0.360952;0.000000;,
  0.000000;0.439525;-0.898230;,
  -0.384098;0.438627;0.812450;,
  0.000000;0.439527;0.898230;,
  -0.918909;0.394469;0.000000;;
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
  4;38,47,2,1;,
  4;46,10,9,2;,
  4;34,40,26,33;,
  4;40,41,25,26;,
  4;41,17,24,25;,
  4;35,42,48,34;,
  4;43,43,43,43;,
  4;49,16,17,50;,
  4;6,7,42,35;,
  4;7,8,51,42;,
  4;8,15,16,49;;
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