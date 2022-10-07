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
 36;
 3.65385;44.52060;-6.83564;,
 3.65385;44.52060;28.83338;,
 3.65385;33.85010;28.83338;,
 8.24353;33.85010;-6.83564;,
 3.65385;0.09878;28.83338;,
 8.24353;0.09878;-6.83564;,
 3.65385;44.52060;28.83338;,
 -7.44890;44.52060;28.83338;,
 -7.44890;33.85010;28.83338;,
 3.65385;33.85010;28.83338;,
 -7.44890;0.09878;28.83338;,
 3.65385;0.09878;28.83338;,
 -7.44890;44.52060;28.83338;,
 -4.74731;44.52060;-6.83564;,
 -2.85915;33.85010;-6.83564;,
 -7.44890;33.85010;28.83338;,
 -2.85915;0.09878;-6.83564;,
 -7.44890;0.09878;28.83338;,
 3.65385;44.52060;-6.83564;,
 -4.74731;44.52060;-6.83564;,
 -2.85915;0.09878;-6.83564;,
 8.24353;0.09878;-6.83564;,
 3.65385;33.85010;-28.14449;,
 -7.44890;33.85010;-28.14449;,
 -2.85915;33.85010;-6.83564;,
 8.24353;33.85010;-6.83564;,
 3.65385;0.09878;-28.14449;,
 8.24353;0.09878;-6.83564;,
 -7.44890;0.09878;-28.14449;,
 -2.85915;0.09878;-6.83564;,
 3.65385;44.47807;-10.85751;,
 -4.74731;44.47807;-10.85751;,
 -4.74731;44.52060;-6.83564;,
 3.65385;44.52060;-6.83564;,
 4.86509;35.55052;-10.85751;,
 -2.88893;35.55052;-10.85751;;
 
 18;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,7,8,9;,
 4;9,8,10,11;,
 4;12,13,14,15;,
 4;15,14,16,17;,
 4;12,1,18,19;,
 4;20,21,4,17;,
 4;22,23,24,25;,
 4;26,22,25,27;,
 4;28,26,27,29;,
 4;23,28,29,24;,
 4;23,22,26,28;,
 4;30,31,32,33;,
 4;34,30,33,25;,
 4;35,34,25,24;,
 4;31,35,24,32;,
 4;31,30,34,35;;
 
 MeshMaterialList {
  5;
  18;
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
  2;;
  Material {
   0.800000;0.000000;0.068800;1.000000;;
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
    "data\\TEXTURE\\Player\\pizza_logo.png";
   }
  }
 }
 MeshNormals {
  23;
  -0.988166;-0.138138;-0.066673;,
  -0.997482;-0.069776;-0.012691;,
  -0.999114;0.000000;0.042076;,
  0.967902;0.227269;-0.107306;,
  0.990576;0.114453;-0.075228;,
  0.999114;0.000000;-0.042076;,
  0.977823;0.200647;0.060024;,
  0.990413;0.100893;0.094356;,
  0.991823;0.000000;0.127622;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.977581;0.000000;-0.210560;,
  0.000000;0.999944;-0.010574;,
  0.000000;-0.921060;-0.389420;,
  0.930099;0.247344;-0.271546;,
  -0.991091;-0.086788;-0.101028;,
  -0.992479;-0.043439;-0.114444;,
  -0.991823;0.000000;-0.127624;,
  0.000000;0.999986;-0.005287;,
  -0.977580;0.000000;0.210563;,
  0.000000;0.000000;-1.000000;,
  -0.981461;-0.188960;-0.032062;;
  18;
  4;3,6,7,4;,
  4;4,7,8,5;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;16,0,1,17;,
  4;17,1,2,18;,
  4;10,10,19,19;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;12,12,4,5;,
  4;11,11,11,11;,
  4;20,20,2,1;,
  4;21,21,21,21;,
  4;13,13,19,19;,
  4;15,15,3,4;,
  4;14,14,14,14;,
  4;22,22,1,0;,
  4;21,21,21,21;;
 }
 MeshTextureCoords {
  36;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;;
 }
}
