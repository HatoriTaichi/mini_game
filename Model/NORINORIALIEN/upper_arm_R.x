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
 -0.63603;-19.07222;-2.69655;,
 -0.63603;-10.70794;-2.69655;,
 -0.19140;-10.70794;-1.82998;,
 -0.19140;-19.07222;-1.82998;,
 -0.19140;-10.70794;1.74399;,
 -0.19140;-19.07222;1.74399;,
 -0.63603;-10.70794;2.61056;,
 -0.63603;-19.07222;2.61056;,
 -0.63603;-2.34366;-2.69655;,
 -0.19140;-2.34366;-1.82998;,
 -0.19140;-2.34366;1.74399;,
 -0.63603;-2.34366;2.61056;,
 -0.63603;-19.07222;2.61056;,
 -0.63603;-10.70794;2.61056;,
 -1.53739;-10.70794;3.27825;,
 -1.53739;-19.07222;3.27825;,
 -3.99604;-10.70794;3.27825;,
 -3.99604;-19.07222;3.27825;,
 -4.89741;-10.70794;2.61056;,
 -4.89741;-19.07222;2.61056;,
 -0.63603;-2.34366;2.61056;,
 -1.53739;-2.34366;3.27825;,
 -3.99604;-2.34366;3.27825;,
 -4.89741;-2.34366;2.61056;,
 -4.89741;-19.07222;2.61056;,
 -4.89741;-10.70794;2.61056;,
 -5.34203;-10.70794;1.74399;,
 -5.34203;-19.07222;1.74399;,
 -5.34203;-10.70794;-1.82998;,
 -5.34203;-19.07222;-1.82998;,
 -4.89741;-10.70794;-2.69655;,
 -4.89741;-19.07222;-2.69655;,
 -4.89741;-2.34366;2.61056;,
 -5.34203;-2.34366;1.74399;,
 -5.34203;-2.34366;-1.82998;,
 -4.89741;-2.34366;-2.69655;,
 -4.89741;-19.07222;-2.69655;,
 -4.89741;-10.70794;-2.69655;,
 -3.99604;-10.70794;-3.36423;,
 -3.99604;-19.07222;-3.36423;,
 -1.53739;-10.70794;-3.36423;,
 -1.53739;-19.07222;-3.36423;,
 -0.63603;-10.70794;-2.69655;,
 -0.63603;-19.07222;-2.69655;,
 -4.89741;-2.34366;-2.69655;,
 -3.99604;-2.34366;-3.36423;,
 -1.53739;-2.34366;-3.36423;,
 -0.63603;-2.34366;-2.69655;,
 -3.99604;-19.07222;-3.36423;,
 -3.99604;-22.54983;-1.82998;,
 -5.34203;-19.07222;-1.82998;,
 -3.99604;-22.54983;1.74399;,
 -5.34203;-19.07222;1.74399;,
 -3.99604;-19.07222;3.27825;,
 -1.53739;-19.07222;-3.36423;,
 -1.53739;-22.54983;-1.82998;,
 -1.53739;-22.54983;1.74399;,
 -1.53739;-19.07222;3.27825;,
 -0.63603;-19.07222;-2.69655;,
 -0.19140;-19.07222;-1.82998;,
 -0.19140;-19.07222;1.74399;,
 -0.63603;-19.07222;2.61056;,
 -3.99604;-2.34366;-3.36423;,
 -5.34203;-2.34366;-1.82998;,
 -3.99604;0.79181;-1.82998;,
 -5.34203;-2.34366;1.74399;,
 -3.99604;0.79181;1.74399;,
 -3.99604;-2.34366;3.27825;,
 -1.53739;-2.34366;-3.36423;,
 -1.53739;0.79181;-1.82998;,
 -1.53739;0.79181;1.74399;,
 -1.53739;-2.34366;3.27825;,
 -0.63603;-2.34366;-2.69655;,
 -0.19140;-2.34366;-1.82998;,
 -0.19140;-2.34366;1.74399;,
 -0.63603;-2.34366;2.61056;;
 
 42;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;1,8,9,2;,
 4;2,9,10,4;,
 4;4,10,11,6;,
 4;12,13,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;13,20,21,14;,
 4;14,21,22,16;,
 4;16,22,23,18;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;25,32,33,26;,
 4;26,33,34,28;,
 4;28,34,35,30;,
 4;36,37,38,39;,
 4;39,38,40,41;,
 4;41,40,42,43;,
 4;37,44,45,38;,
 4;38,45,46,40;,
 4;40,46,47,42;,
 4;36,48,49,50;,
 4;50,49,51,52;,
 4;52,51,53,19;,
 4;48,54,55,49;,
 4;49,55,56,51;,
 4;51,56,57,53;,
 4;54,58,59,55;,
 4;55,59,60,56;,
 4;56,60,61,57;,
 4;62,44,63,64;,
 4;64,63,65,66;,
 4;66,65,23,67;,
 4;68,62,64,69;,
 4;69,64,66,70;,
 4;70,66,67,71;,
 4;72,68,69,73;,
 4;73,69,70,74;,
 4;74,70,71,75;;
 
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
  0.757402;-0.116130;-0.642538;,
  0.940933;-0.185706;-0.283121;,
  0.940934;-0.185706;0.283120;,
  0.762484;0.000000;-0.647007;,
  0.972039;0.000000;-0.234818;,
  0.972039;0.000000;0.234819;,
  0.756353;0.127500;-0.641618;,
  0.937583;0.203721;-0.281844;,
  0.937583;0.203721;0.281844;,
  0.757404;-0.116130;0.642537;,
  0.359472;-0.202959;0.910817;,
  -0.359471;-0.202959;0.910817;,
  0.762485;0.000000;0.647005;,
  0.313408;0.000000;0.949619;,
  -0.313406;0.000000;0.949619;,
  0.756354;0.127500;0.641617;,
  0.358051;0.222231;0.906870;,
  -0.358051;0.222232;0.906870;,
  -0.757404;-0.116131;0.642536;,
  -0.940934;-0.185707;0.283119;,
  -0.940934;-0.185707;-0.283119;,
  -0.762486;0.000000;0.647005;,
  -0.972040;0.000000;0.234816;,
  -0.972040;0.000000;-0.234816;,
  -0.756355;0.127500;0.641616;,
  -0.937583;0.203721;0.281842;,
  -0.937583;0.203722;-0.281842;,
  -0.757403;-0.116131;-0.642537;,
  -0.359469;-0.202959;-0.910818;,
  0.359470;-0.202958;-0.910818;,
  -0.762485;0.000000;-0.647006;,
  -0.313404;0.000000;-0.949620;,
  0.313405;0.000000;-0.949619;,
  -0.756353;0.127501;-0.641618;,
  -0.358049;0.222231;-0.906871;,
  0.358049;0.222231;-0.906870;,
  -0.871963;-0.369134;-0.321590;,
  -0.871964;-0.369133;0.321589;,
  0.659627;-0.440563;-0.608931;,
  0.000000;-1.000000;-0.000000;,
  -0.858518;0.403124;-0.316920;,
  -0.858518;0.403124;0.316919;,
  0.646132;0.477880;-0.595100;,
  0.000000;1.000000;0.000000;,
  -0.000000;-0.403644;-0.914916;,
  0.000000;-0.403645;0.914916;,
  0.390111;-0.402881;0.827949;,
  0.932584;-0.360952;-0.000000;,
  -0.000000;0.439525;-0.898230;,
  0.384098;0.438627;0.812450;,
  0.000000;0.439527;0.898230;,
  0.918909;0.394469;0.000000;;
  42;
  4;0,3,4,1;,
  4;1,4,5,2;,
  4;2,5,12,9;,
  4;3,6,7,4;,
  4;4,7,8,5;,
  4;5,8,15,12;,
  4;9,12,13,10;,
  4;10,13,14,11;,
  4;11,14,21,18;,
  4;12,15,16,13;,
  4;13,16,17,14;,
  4;14,17,24,21;,
  4;18,21,22,19;,
  4;19,22,23,20;,
  4;20,23,30,27;,
  4;21,24,25,22;,
  4;22,25,26,23;,
  4;23,26,33,30;,
  4;27,30,31,28;,
  4;28,31,32,29;,
  4;29,32,3,0;,
  4;30,33,34,31;,
  4;31,34,35,32;,
  4;32,35,6,3;,
  4;27,28,36,20;,
  4;20,36,37,19;,
  4;19,37,11,18;,
  4;28,29,38,44;,
  4;39,39,39,39;,
  4;45,46,10,11;,
  4;29,0,1,38;,
  4;38,1,2,47;,
  4;46,2,9,10;,
  4;34,33,26,40;,
  4;40,26,25,41;,
  4;41,25,24,17;,
  4;35,34,48,42;,
  4;43,43,43,43;,
  4;49,50,17,16;,
  4;6,35,42,7;,
  4;7,42,51,8;,
  4;8,49,16,15;;
 }
 MeshTextureCoords {
  76;
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.333333;0.000000;,
  0.666667;0.500000;,
  0.666667;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.333333;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.333333;0.000000;,
  0.666667;0.500000;,
  0.666667;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.333333;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.333333;0.000000;,
  0.666667;0.500000;,
  0.666667;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.333333;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.333333;0.000000;,
  0.666667;0.500000;,
  0.666667;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.333333;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.000000;0.333333;,
  0.333333;0.333333;,
  0.333333;0.000000;,
  0.666667;0.333333;,
  0.666667;0.000000;,
  1.000000;0.333333;,
  0.000000;0.666667;,
  0.333333;0.666667;,
  0.666667;0.666667;,
  1.000000;0.666667;,
  0.000000;1.000000;,
  0.333333;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666667;,
  0.333333;1.000000;,
  0.333333;0.666667;,
  0.666667;1.000000;,
  0.666667;0.666667;,
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
