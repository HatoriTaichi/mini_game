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
 24;
 -20.81658;63.66334;-18.34888;,
 20.81658;63.66334;-18.34888;,
 27.93879;15.31969;-25.47108;,
 -27.93879;15.31969;-25.47108;,
 20.81658;63.66334;-18.34888;,
 20.81658;63.66334;23.28432;,
 27.93879;15.31969;30.40653;,
 27.93879;15.31969;-25.47108;,
 20.81658;63.66334;23.28432;,
 -20.81658;63.66334;23.28432;,
 -27.93879;15.31969;30.40653;,
 27.93879;15.31969;30.40653;,
 -20.81658;63.66334;23.28432;,
 -20.81658;63.66334;-18.34888;,
 -27.93879;15.31969;-25.47108;,
 -27.93879;15.31969;30.40653;,
 20.81658;63.66334;-18.34888;,
 -20.81658;63.66334;-18.34888;,
 29.95936;0.10946;-28.09536;,
 -29.95936;0.10946;-28.09536;,
 -27.93879;15.31969;-25.47108;,
 27.93879;15.31969;-25.47108;,
 29.95936;0.10946;33.03079;,
 -29.95936;0.10946;33.03079;;
 
 10;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,20,21;,
 4;22,18,21,6;,
 4;23,22,6,15;,
 4;19,23,15,20;,
 4;19,18,22,23;;
 
 MeshMaterialList {
  5;
  10;
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1;;
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
  14;
  0.000000;0.145751;-0.989321;,
  0.000000;0.157898;-0.987455;,
  0.989321;0.145751;0.000000;,
  0.990331;0.138722;0.000000;,
  0.000000;0.145751;0.989321;,
  0.000000;0.157898;0.987455;,
  0.000000;0.170022;-0.985440;,
  0.991292;0.131686;0.000000;,
  0.000000;0.170021;0.985440;,
  -0.989321;0.145751;0.000000;,
  -0.990331;0.138722;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.991292;0.131686;0.000000;,
  0.000000;-1.000000;-0.000000;;
  10;
  4;0,0,1,1;,
  4;2,2,3,3;,
  4;4,4,5,5;,
  4;9,9,10,10;,
  4;11,11,11,11;,
  4;6,6,1,1;,
  4;7,7,3,3;,
  4;8,8,5,5;,
  4;12,12,10,10;,
  4;13,13,13,13;;
 }
 MeshTextureCoords {
  24;
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
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
