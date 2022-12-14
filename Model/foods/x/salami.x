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
 0.03325;3.20000;-29.97236;,
 17.64295;3.20000;-24.25075;,
 17.54314;0.07077;-24.25075;,
 0.43954;0.14911;-29.97236;,
 28.52638;3.20000;-9.27108;,
 28.42651;0.07077;-9.27108;,
 28.52638;3.20000;9.24483;,
 28.42651;0.07077;9.24483;,
 18.04923;3.20000;24.22452;,
 17.54314;0.07077;24.22452;,
 0.43954;3.20001;29.94622;,
 -0.06660;0.07077;29.94622;,
 -17.17016;3.20000;24.22452;,
 -17.67629;0.07077;24.22452;,
 -28.45985;3.20000;9.24483;,
 -28.55970;0.07077;9.24483;,
 -28.45983;3.20000;-9.27111;,
 -28.55970;0.07077;-9.27111;,
 -17.57645;3.20000;-24.25075;,
 -17.67629;0.07077;-24.25075;,
 0.03325;3.20000;-0.01313;,
 -0.06660;0.07077;-0.01313;;
 
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
    "data\\Texture\\Foods\\salami.jpg";
   }
  }
 }
 MeshNormals {
  20;
  -0.000000;1.000000;-0.000000;,
  0.004255;0.000212;-0.999991;,
  0.589490;-0.005412;-0.807758;,
  0.950610;-0.030335;-0.308903;,
  0.950977;-0.057725;0.303826;,
  0.589846;-0.067367;0.804701;,
  -0.000000;0.000001;1.000000;,
  -0.582725;0.066654;0.809932;,
  -0.948262;0.057367;0.312263;,
  -0.950610;0.030335;-0.308903;,
  -0.586044;0.005633;-0.810260;,
  -0.000017;-1.000000;-0.000523;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.000084;-0.999997;-0.002616;,
  -0.001842;-0.999997;-0.001339;,
  0.000000;-1.000000;0.000000;,
  0.001759;-0.999998;-0.001278;;
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
  3;0,12,12;,
  3;0,12,12;,
  3;0,12,12;,
  3;0,13,12;,
  3;0,14,13;,
  3;0,15,14;,
  3;0,12,15;,
  3;0,12,12;,
  3;0,12,12;,
  3;0,12,12;,
  3;11,16,17;,
  3;11,17,18;,
  3;11,18,18;,
  3;11,18,18;,
  3;11,18,18;,
  3;11,18,18;,
  3;11,18,18;,
  3;11,18,18;,
  3;11,18,19;,
  3;11,19,16;;
 }
 MeshTextureCoords {
  22;
  0.283870;0.312016;,
  0.352371;0.334277;,
  0.351983;0.340750;,
  0.285450;0.318327;,
  0.394708;0.392559;,
  0.394319;0.399032;,
  0.394708;0.464600;,
  0.394320;0.471073;,
  0.353953;0.522882;,
  0.351984;0.529356;,
  0.285451;0.545144;,
  0.283482;0.551618;,
  0.216950;0.522883;,
  0.214981;0.529357;,
  0.173033;0.464601;,
  0.172645;0.471074;,
  0.173033;0.392560;,
  0.172644;0.399033;,
  0.215369;0.334277;,
  0.214980;0.340751;,
  0.283870;0.428580;,
  0.283482;0.435053;;
 }
}
