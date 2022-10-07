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
 3.98742;19.96326;-3.27388;,
 3.98742;19.96326;12.54670;,
 3.98742;15.23043;12.54670;,
 8.05925;15.23043;-3.27388;,
 3.98742;0.26042;12.54670;,
 8.05925;0.26042;-3.27388;,
 3.98742;19.96326;12.54670;,
 -5.86283;19.96326;12.54670;,
 -5.86283;15.23043;12.54670;,
 3.98742;15.23043;12.54670;,
 -5.86283;0.26042;12.54670;,
 3.98742;0.26042;12.54670;,
 -5.86283;19.96326;12.54670;,
 -3.46605;19.96326;-3.27388;,
 -1.79103;15.23043;-3.27388;,
 -5.86283;15.23043;12.54670;,
 -1.79103;0.26042;-3.27388;,
 -5.86283;0.26042;12.54670;,
 3.98742;19.96326;-3.27388;,
 -3.46605;19.96326;-3.27388;,
 -1.79103;0.26042;-3.27388;,
 8.05925;0.26042;-3.27388;,
 3.98742;15.23043;-12.72523;,
 -5.86283;15.23043;-12.72523;,
 -1.79103;15.23043;-3.27388;,
 8.05925;15.23043;-3.27388;,
 3.98742;0.26042;-12.72523;,
 8.05925;0.26042;-3.27388;,
 -5.86283;0.26042;-12.72523;,
 -1.79103;0.26042;-3.27388;,
 3.98742;19.94437;-5.05771;,
 -3.46605;19.94437;-5.05771;,
 -3.46605;19.96326;-3.27388;,
 3.98742;19.96326;-3.27388;,
 5.06187;15.98465;-5.05771;,
 -1.81738;15.98465;-5.05771;;
 
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
  23;
  -0.955962;-0.263444;-0.129359;,
  -0.990171;-0.136847;-0.028896;,
  -0.997003;0.000000;0.077363;,
  0.911310;0.383665;-0.149385;,
  0.973317;0.197922;-0.116110;,
  0.997003;0.000000;-0.077364;,
  0.933817;0.342742;0.102533;,
  0.968248;0.174456;0.179059;,
  0.968439;0.000000;0.249252;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.918396;0.000000;-0.395664;,
  0.000000;0.999944;-0.010593;,
  0.000000;-0.921056;-0.389430;,
  0.828980;0.399403;-0.391498;,
  -0.966761;-0.164556;-0.195690;,
  -0.971243;-0.082588;-0.223308;,
  -0.968439;0.000000;-0.249250;,
  0.000000;0.999986;-0.005296;,
  -0.918397;0.000000;0.395661;,
  0.000000;0.000000;-1.000000;,
  -0.931497;-0.358567;-0.061179;;
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