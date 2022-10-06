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
 22;
 0.00000;20.01028;0.50917;,
 5.87785;18.10046;0.50917;,
 5.70892;18.10046;-0.53532;,
 0.00000;20.01028;-0.50917;,
 9.51057;13.10046;0.50917;,
 9.34163;13.10046;-0.53532;,
 9.51057;6.92012;0.50917;,
 9.34163;6.92012;-0.53532;,
 5.87785;1.92012;0.50917;,
 5.70892;1.92012;-0.53532;,
 0.00000;0.01029;0.50917;,
 -0.16894;0.01029;-0.53532;,
 -5.87785;1.92012;0.50917;,
 -6.04679;1.92012;-0.53532;,
 -9.51057;6.92012;0.50917;,
 -9.67950;6.92012;-0.53532;,
 -9.51056;13.10047;0.50917;,
 -9.67950;13.10047;-0.53532;,
 -5.87785;18.10046;0.50917;,
 -6.04679;18.10046;-0.53532;,
 0.00000;10.01029;0.50917;,
 -0.16894;10.01029;-0.53532;;
 
 30;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,0,3,19;,
 3;20,1,0;,
 3;20,4,1;,
 3;20,6,4;,
 3;20,8,6;,
 3;20,10,8;,
 3;20,12,10;,
 3;20,14,12;,
 3;20,16,14;,
 3;20,18,16;,
 3;20,0,18;,
 3;21,3,2;,
 3;21,2,5;,
 3;21,5,7;,
 3;21,7,9;,
 3;21,9,11;,
 3;21,11,13;,
 3;21,13,15;,
 3;21,15,17;,
 3;21,17,19;,
 3;21,19,3;;
 
 MeshMaterialList {
  1;
  30;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\mini_game\\Model\\foods\\texture\\salami.jpg";
   }
  }
 }
 MeshNormals {
  16;
  0.000000;0.000000;1.000000;,
  0.004174;0.999991;-0.000324;,
  0.586521;0.805836;-0.081366;,
  0.939785;0.306102;-0.152003;,
  0.939785;-0.306102;-0.152003;,
  0.584207;-0.806085;-0.094489;,
  -0.000000;-1.000000;0.000001;,
  -0.584207;-0.806085;0.094490;,
  -0.939786;-0.306102;0.152000;,
  -0.939785;0.306102;0.152002;,
  -0.583144;0.808305;0.081155;,
  -0.000017;0.000523;-1.000000;,
  -0.000084;0.002616;-0.999997;,
  -0.001842;0.001339;-0.999997;,
  0.000000;0.000000;-1.000000;,
  0.001759;0.001278;-0.999998;;
  30;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,1,1,10;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;11,12,13;,
  3;11,13,14;,
  3;11,14,14;,
  3;11,14,14;,
  3;11,14,14;,
  3;11,14,14;,
  3;11,14,14;,
  3;11,14,14;,
  3;11,14,15;,
  3;11,15,12;;
 }
 MeshTextureCoords {
  22;
  0.285975;0.312159;,
  0.356206;0.334527;,
  0.354188;0.334527;,
  0.285975;0.312159;,
  0.399611;0.393089;,
  0.397593;0.393089;,
  0.399611;0.465476;,
  0.397593;0.465476;,
  0.356206;0.524038;,
  0.354188;0.524038;,
  0.285975;0.546407;,
  0.283956;0.546407;,
  0.215744;0.524038;,
  0.213725;0.524038;,
  0.172339;0.465476;,
  0.170320;0.465476;,
  0.172339;0.393089;,
  0.170320;0.393089;,
  0.215744;0.334527;,
  0.213725;0.334527;,
  0.285975;0.429283;,
  0.283956;0.429283;;
 }
}
