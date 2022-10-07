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
 -3.62722;44.45154;-7.10856;,
 -8.21693;33.78103;-7.10856;,
 -3.62722;33.78103;28.56046;,
 -3.62722;44.45154;28.56046;,
 -8.21693;0.02971;-7.10856;,
 -3.62722;0.02971;28.56046;,
 -3.62722;44.45154;28.56046;,
 -3.62722;33.78103;28.56046;,
 7.47549;33.78103;28.56046;,
 7.47549;44.45154;28.56046;,
 -3.62722;0.02971;28.56046;,
 7.47549;0.02971;28.56046;,
 7.47549;44.45154;28.56046;,
 7.47549;33.78103;28.56046;,
 2.88576;33.78103;-7.10856;,
 4.77392;44.45154;-7.10856;,
 7.47549;0.02971;28.56046;,
 2.88576;0.02971;-7.10856;,
 4.77392;44.45154;-7.10856;,
 -3.62722;44.45154;-7.10856;,
 2.88576;0.02971;-7.10856;,
 -8.21693;0.02971;-7.10856;,
 -3.62722;33.78103;-28.41740;,
 -8.21693;33.78103;-7.10856;,
 2.88576;33.78103;-7.10856;,
 7.47549;33.78103;-28.41740;,
 -3.62722;0.02971;-28.41740;,
 -8.21693;0.02971;-7.10856;,
 7.47549;0.02971;-28.41740;,
 2.88576;0.02971;-7.10856;,
 -3.62722;44.40902;-11.13043;,
 -3.62722;44.45154;-7.10856;,
 4.77392;44.45154;-7.10856;,
 4.77392;44.40902;-11.13043;,
 -4.83848;35.48145;-11.13043;,
 2.91555;35.48145;-11.13043;;
 
 18;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;12,18,19,3;,
 4;20,16,5,21;,
 4;22,23,24,25;,
 4;26,27,23,22;,
 4;28,29,27,26;,
 4;25,24,29,28;,
 4;25,28,26,22;,
 4;30,31,32,33;,
 4;34,23,31,30;,
 4;35,24,23,34;,
 4;33,32,24,35;,
 4;33,35,34,30;;
 
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
    "data\\Texture\\Player\\pizza_logo.png";
   }
  }
 }
 MeshNormals {
  23;
  0.988166;-0.138138;-0.066672;,
  0.997482;-0.069776;-0.012690;,
  0.999114;0.000000;0.042076;,
  -0.967902;0.227270;-0.107306;,
  -0.990576;0.114453;-0.075228;,
  -0.999114;0.000000;-0.042076;,
  -0.977823;0.200648;0.060025;,
  -0.990413;0.100893;0.094356;,
  -0.991823;0.000000;0.127623;,
  0.000000;-0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.977581;0.000000;-0.210561;,
  0.000000;0.999944;-0.010573;,
  0.000000;-0.921060;-0.389420;,
  -0.930098;0.247345;-0.271546;,
  0.991091;-0.086788;-0.101028;,
  0.992480;-0.043439;-0.114444;,
  0.991823;0.000000;-0.127623;,
  0.000000;0.999986;-0.005287;,
  0.977580;0.000000;0.210562;,
  0.000000;0.000000;-1.000000;,
  0.981461;-0.188959;-0.032061;;
  18;
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;16,17,1,0;,
  4;17,18,2,1;,
  4;10,19,19,10;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;12,5,4,12;,
  4;11,11,11,11;,
  4;20,1,2,20;,
  4;21,21,21,21;,
  4;13,19,19,13;,
  4;15,4,3,15;,
  4;14,14,14,14;,
  4;22,0,1,22;,
  4;21,21,21,21;;
 }
 MeshTextureCoords {
  36;
  0.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;;
 }
}
