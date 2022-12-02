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
 28;
 258.21075;0.00000;-42.15208;,
 258.21075;-34.26537;-25.65075;,
 -258.21075;-34.26537;-25.65075;,
 -258.21075;0.00000;-42.15208;,
 258.21075;-42.72818;11.42740;,
 -258.21075;-42.72818;11.42740;,
 258.21075;-19.01584;41.16177;,
 -258.21075;-19.01584;41.16177;,
 258.21075;19.01584;41.16177;,
 -258.21075;19.01584;41.16177;,
 258.21075;42.72818;11.42740;,
 -258.21075;42.72818;11.42740;,
 258.21075;34.26531;-25.65075;,
 -258.21075;34.26531;-25.65075;,
 258.21075;0.00000;-42.15208;,
 258.21075;34.26531;-25.65075;,
 258.21075;42.72818;11.42740;,
 258.21075;19.01584;41.16177;,
 258.21075;-19.01584;41.16177;,
 258.21075;-34.26537;-25.65075;,
 258.21075;-42.72818;11.42740;,
 -258.21075;-19.01584;41.16177;,
 -258.21075;19.01584;41.16177;,
 -258.21075;42.72818;11.42740;,
 -258.21075;34.26531;-25.65075;,
 -258.21075;0.00000;-42.15208;,
 -258.21075;-42.72818;11.42740;,
 -258.21075;-34.26537;-25.65075;;
 
 13;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,0,3,13;,
 4;14,15,16,17;,
 4;17,18,19,14;,
 3;20,19,18;,
 4;21,22,23,24;,
 4;25,26,21,24;,
 3;26,25,27;;
 
 MeshMaterialList {
  2;
  13;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\tree.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\tree.jpg";
   }
  }
 }
 MeshNormals {
  10;
  0.000000;0.000000;-1.000000;,
  0.000000;-0.781832;-0.623489;,
  0.000000;-0.974928;0.222521;,
  0.000000;-0.433884;0.900969;,
  0.000000;0.433884;0.900969;,
  0.000000;0.974928;0.222520;,
  0.000000;0.781831;-0.623490;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;;
  13;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,0,0,6;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  3;8,7,7;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  3;9,9,9;;
 }
 MeshTextureCoords {
  28;
  4.803513;0.500000;,
  4.803513;2.213268;,
  -3.803513;2.213268;,
  -3.803513;0.500000;,
  4.803513;2.636409;,
  -3.803513;2.636409;,
  4.803513;1.450792;,
  -3.803513;1.450792;,
  4.803513;-0.450792;,
  -3.803513;-0.450792;,
  4.803513;-1.636409;,
  -3.803513;-1.636409;,
  4.803513;-1.213266;,
  -3.803513;-1.213266;,
  0.612638;-1.607604;,
  2.325838;-0.782537;,
  2.748966;1.071370;,
  1.563394;2.558088;,
  -0.338118;2.558088;,
  -1.100565;-0.782537;,
  -1.523690;1.071370;,
  -0.563394;2.558088;,
  1.338118;2.558088;,
  2.523690;1.071370;,
  2.100563;-0.782537;,
  0.387362;-1.607604;,
  -1.748966;1.071370;,
  -1.325841;-0.782537;;
 }
}
