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
 41;
 -7.54862;10.10611;0.00000;,
 -9.23384;6.27927;0.00000;,
 -9.23384;7.40013;2.01617;,
 -7.54862;10.10611;0.00000;,
 -9.23384;7.40013;-2.01617;,
 -7.06613;3.03504;0.00000;,
 -7.06613;5.10611;3.72539;,
 -7.06613;5.10611;-3.72539;,
 -3.82189;0.86731;0.00000;,
 -3.82189;3.57329;4.86745;,
 -3.82189;3.57329;-4.86746;,
 0.00495;0.10611;0.00000;,
 0.00495;3.03504;5.26850;,
 0.00495;3.03504;-5.26850;,
 3.83179;0.86731;0.00000;,
 3.83179;3.57329;4.86745;,
 3.83179;3.57329;-4.86746;,
 7.07602;3.03504;0.00000;,
 7.07602;5.10611;3.72539;,
 7.07602;5.10611;-3.72539;,
 9.24374;6.27927;0.00000;,
 9.24374;7.40013;2.01617;,
 9.24374;7.40013;-2.01617;,
 10.00494;10.10611;0.00000;,
 10.00494;10.10611;0.00000;,
 -7.54862;10.10611;0.00000;,
 10.00494;10.10611;0.00000;,
 9.24374;7.40013;-2.01617;,
 -3.82189;3.57329;4.86745;,
 0.00495;3.03504;5.26850;,
 -9.23384;7.40013;-2.01617;,
 -3.82189;3.57329;-4.86746;,
 -7.06613;5.10611;-3.72539;,
 3.83179;3.57329;-4.86746;,
 0.00495;3.03504;-5.26850;,
 7.07602;5.10611;-3.72539;,
 7.07602;5.10611;3.72539;,
 9.24374;7.40013;2.01617;,
 3.83179;3.57329;4.86745;,
 -9.23384;7.40013;2.01617;,
 -7.06613;5.10611;3.72539;;
 
 24;
 3;0,1,2;,
 3;3,4,1;,
 4;2,1,5,6;,
 4;1,4,7,5;,
 4;6,5,8,9;,
 4;5,7,10,8;,
 4;9,8,11,12;,
 4;8,10,13,11;,
 4;12,11,14,15;,
 4;11,13,16,14;,
 4;15,14,17,18;,
 4;14,16,19,17;,
 4;18,17,20,21;,
 4;17,19,22,20;,
 3;21,20,23;,
 3;20,22,24;,
 3;25,26,27;,
 3;25,28,29;,
 4;30,25,31,32;,
 4;33,34,31,25;,
 4;27,35,33,25;,
 4;36,37,26,25;,
 4;36,25,29,38;,
 4;39,40,28,25;;
 
 MeshMaterialList {
  2;
  24;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\mini_game\\Model\\foods\\texture\\tomato.jpg";
   }
  }
  Material {
   0.759200;0.000000;0.109600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  40;
  -0.915191;0.403021;0.000000;,
  -0.893049;0.393271;-0.218633;,
  -0.996694;-0.081245;0.000000;,
  -0.893049;0.393271;0.218633;,
  -0.661884;-0.655168;0.364230;,
  -0.710703;-0.703492;0.000000;,
  -0.661884;-0.655168;-0.364230;,
  -0.343228;-0.820922;0.456378;,
  -0.385742;-0.922607;0.000000;,
  -0.343228;-0.820923;-0.456378;,
  0.000000;-0.874017;0.485895;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.874017;-0.485895;,
  0.343229;-0.820922;0.456378;,
  0.385743;-0.922606;0.000000;,
  0.343228;-0.820922;-0.456378;,
  0.661884;-0.655168;0.364230;,
  0.710703;-0.703492;0.000000;,
  0.661884;-0.655168;-0.364230;,
  0.905500;-0.370886;0.206189;,
  0.925384;-0.379031;-0.000000;,
  0.905500;-0.370886;-0.206189;,
  0.980786;-0.195089;-0.000000;,
  -0.794442;-0.530825;0.295104;,
  -0.794442;-0.530825;-0.295104;,
  0.000000;0.597471;-0.801890;,
  0.000000;0.597472;-0.801890;,
  0.000000;0.597471;-0.801891;,
  -0.000000;0.597471;0.801891;,
  -0.000000;0.597470;0.801891;,
  -0.000001;0.597470;0.801891;,
  0.000001;0.597471;-0.801890;,
  0.000000;0.597472;-0.801890;,
  0.000000;0.597471;-0.801890;,
  0.000000;0.597472;-0.801890;,
  0.000000;0.597470;-0.801891;,
  -0.000001;0.597471;0.801890;,
  -0.000002;0.597472;0.801890;,
  0.000001;0.597471;0.801891;,
  0.000003;0.597472;0.801890;;
  24;
  3;0,2,1;,
  3;0,3,2;,
  4;23,2,5,4;,
  4;2,24,6,5;,
  4;4,5,8,7;,
  4;5,6,9,8;,
  4;7,8,11,10;,
  4;8,9,12,11;,
  4;10,11,14,13;,
  4;11,12,15,14;,
  4;13,14,17,16;,
  4;14,15,18,17;,
  4;16,17,20,19;,
  4;17,18,21,20;,
  3;19,20,22;,
  3;20,21,22;,
  3;25,26,27;,
  3;28,29,30;,
  4;31,25,32,31;,
  4;33,34,32,25;,
  4;27,35,33,25;,
  4;36,37,37,28;,
  4;36,28,30,38;,
  4;39,39,29,28;;
 }
 MeshTextureCoords {
  41;
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.625000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.750000;0.250000;,
  0.625000;0.250000;,
  0.875000;0.250000;,
  0.750000;0.375000;,
  0.625000;0.375000;,
  0.875000;0.375000;,
  0.750000;0.500000;,
  0.625000;0.500000;,
  0.875000;0.500000;,
  0.750000;0.625000;,
  0.625000;0.625000;,
  0.875000;0.625000;,
  0.750000;0.750000;,
  0.625000;0.750000;,
  0.875000;0.750000;,
  0.750000;0.875000;,
  0.625000;0.875000;,
  0.875000;0.875000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.311233;0.487169;,
  0.734963;0.487169;,
  0.716589;0.575717;,
  0.401193;0.700943;,
  0.493571;0.718557;,
  0.270552;0.575717;,
  0.401193;0.700943;,
  0.322879;0.650785;,
  0.585948;0.700943;,
  0.493571;0.718557;,
  0.664261;0.650785;,
  0.664261;0.650785;,
  0.716589;0.575717;,
  0.585948;0.700943;,
  0.270552;0.575717;,
  0.322879;0.650785;;
 }
}
