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
 145;
 0.00000;13.95862;-9.23879;,
 6.87599;13.95862;-6.53281;,
 7.07107;10.13179;-7.07107;,
 0.00000;10.13179;-10.00000;,
 9.23879;13.95862;0.00000;,
 9.32556;10.13179;0.00000;,
 6.53281;13.95862;6.53281;,
 7.07107;10.13179;7.07107;,
 0.00000;13.95862;9.23879;,
 0.00000;10.13179;9.34206;,
 -6.53282;13.95862;6.53281;,
 -7.07107;10.13179;7.07107;,
 -9.23879;13.95862;0.00000;,
 -9.32556;10.13179;0.00000;,
 -6.86368;13.95862;-6.53281;,
 -7.07107;10.13179;-7.07107;,
 0.00000;13.95862;-9.23879;,
 0.00000;10.13179;-10.00000;,
 6.53281;6.30495;-6.53281;,
 0.00000;6.30495;-9.23879;,
 8.53018;6.30495;0.00000;,
 6.53281;6.30495;6.53281;,
 0.00000;6.30495;9.23879;,
 -6.53282;6.30495;6.53281;,
 -8.53018;6.30495;0.00000;,
 -6.53282;6.30495;-6.53281;,
 0.00000;6.30495;-9.23879;,
 5.00000;3.06072;-5.00000;,
 0.00000;3.06072;-7.07107;,
 7.07107;3.06072;0.00000;,
 5.00000;3.06072;5.00000;,
 0.00000;3.06072;7.07107;,
 -5.00000;3.06072;5.00000;,
 -7.07107;3.06072;0.00000;,
 -5.00000;3.06072;-5.00000;,
 0.00000;3.06072;-7.07107;,
 2.70598;0.89299;-2.70598;,
 0.00000;0.89299;-3.82683;,
 3.82683;0.89299;0.00000;,
 2.70598;0.89299;2.70598;,
 0.00000;0.89299;3.82683;,
 -2.70598;0.89299;2.70598;,
 -3.82683;0.89299;0.00000;,
 -2.70598;0.89299;-2.70598;,
 0.00000;0.89299;-3.82683;,
 0.00000;0.13179;0.00000;,
 0.00000;0.13179;0.00000;,
 0.00000;0.13179;0.00000;,
 0.00000;0.13179;0.00000;,
 0.00000;0.13179;0.00000;,
 0.00000;0.13179;0.00000;,
 0.00000;0.13179;0.00000;,
 0.00000;0.13179;0.00000;,
 2.74333;11.38298;-8.91475;,
 4.20163;11.38298;-8.91475;,
 4.20163;7.38913;-8.91475;,
 2.74333;7.38913;-8.91475;,
 4.20163;11.38298;-8.91475;,
 4.20163;11.38298;-6.98658;,
 4.20163;7.38913;-6.98658;,
 4.20163;7.38913;-8.91475;,
 4.20163;11.38298;-6.98658;,
 2.74333;11.38298;-6.98658;,
 2.74333;7.38913;-6.98658;,
 4.20163;7.38913;-6.98658;,
 2.74333;11.38298;-6.98658;,
 2.74333;11.38298;-8.91475;,
 2.74333;7.38913;-8.91475;,
 2.74333;7.38913;-6.98658;,
 4.20163;11.38298;-8.91475;,
 2.74333;11.38298;-8.91475;,
 2.74333;7.38913;-8.91475;,
 4.20163;7.38913;-8.91475;,
 -4.11510;11.38298;-8.91475;,
 -2.65680;11.38298;-8.91475;,
 -2.65680;7.38913;-8.91475;,
 -4.11510;7.38913;-8.91475;,
 -2.65680;11.38298;-8.91475;,
 -2.65680;11.38298;-6.98658;,
 -2.65680;7.38913;-6.98658;,
 -2.65680;7.38913;-8.91475;,
 -2.65680;11.38298;-6.98658;,
 -4.11510;11.38298;-6.98658;,
 -4.11510;7.38913;-6.98658;,
 -2.65680;7.38913;-6.98658;,
 -4.11510;11.38298;-6.98658;,
 -4.11510;11.38298;-8.91475;,
 -4.11510;7.38913;-8.91475;,
 -4.11510;7.38913;-6.98658;,
 -2.65680;11.38298;-8.91475;,
 -4.11510;11.38298;-8.91475;,
 -4.11510;7.38913;-8.91475;,
 -2.65680;7.38913;-8.91475;,
 0.00000;20.95969;0.00000;,
 2.92631;20.12764;-2.92631;,
 0.00000;20.12764;-4.13843;,
 0.00000;20.95969;0.00000;,
 4.13843;20.12764;0.00000;,
 0.00000;20.95969;0.00000;,
 2.92631;20.12764;2.92631;,
 0.00000;20.95969;0.00000;,
 0.00000;20.12764;4.13843;,
 0.00000;20.95969;0.00000;,
 -2.92631;20.12764;2.92631;,
 0.00000;20.95969;0.00000;,
 -4.13843;20.12764;0.00000;,
 0.00000;20.95969;0.00000;,
 -2.92631;20.12764;-2.92631;,
 0.00000;20.95969;0.00000;,
 0.00000;20.12764;-4.13843;,
 5.39749;17.76839;-5.39749;,
 0.00000;17.76839;-7.63321;,
 7.63321;17.76839;0.00000;,
 5.39749;17.76839;5.39749;,
 0.00000;17.76839;7.63321;,
 -5.39749;17.76839;5.39749;,
 -7.63321;17.76839;0.00000;,
 -5.39749;17.76839;-5.39749;,
 0.00000;17.76839;-7.63321;,
 7.00358;14.40347;-7.00358;,
 -0.00163;15.28698;-9.90456;,
 9.90456;14.40347;0.00000;,
 7.00358;14.40347;7.00358;,
 0.00000;14.40347;9.90456;,
 -7.00359;14.40347;7.00358;,
 -9.90456;14.40347;0.00000;,
 -7.00359;14.40347;-7.00358;,
 -0.00163;15.28698;-9.90456;,
 5.72394;12.80833;-12.69955;,
 -0.00163;13.62341;-15.47610;,
 5.70341;12.36348;-12.67911;,
 -0.00163;13.17857;-15.44491;,
 -0.00163;13.62341;-15.47610;,
 -5.72942;12.80833;-12.62559;,
 -5.74746;12.36348;-12.55721;,
 -0.00163;13.17857;-15.44491;,
 -0.08973;20.03913;-4.29150;,
 2.81195;20.03913;-3.12645;,
 3.19894;18.10636;-6.02198;,
 -0.08972;18.10636;-8.15458;,
 -2.99140;20.03913;-3.05685;,
 -3.37839;18.10636;-6.18389;,
 3.79919;15.21372;-7.95546;,
 -0.08972;15.21372;-10.03005;,
 -3.97865;15.21372;-7.95904;;
 
 94;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;28,27,36,37;,
 4;27,29,38,36;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 3;37,36,45;,
 3;36,38,46;,
 3;38,39,47;,
 3;39,40,48;,
 3;40,41,49;,
 3;41,42,50;,
 3;42,43,51;,
 3;43,44,52;,
 4;53,54,55,56;,
 4;57,58,59,60;,
 4;61,62,63,64;,
 4;65,66,67,68;,
 4;65,58,69,70;,
 4;71,72,59,68;,
 4;73,74,75,76;,
 4;77,78,79,80;,
 4;81,82,83,84;,
 4;85,86,87,88;,
 4;85,78,89,90;,
 4;91,92,79,88;,
 3;93,94,95;,
 3;96,97,94;,
 3;98,99,97;,
 3;100,101,99;,
 3;102,103,101;,
 3;104,105,103;,
 3;106,107,105;,
 3;108,109,107;,
 4;95,94,110,111;,
 4;94,97,112,110;,
 4;97,99,113,112;,
 4;99,101,114,113;,
 4;101,103,115,114;,
 4;103,105,116,115;,
 4;105,107,117,116;,
 4;107,109,118,117;,
 4;111,110,119,120;,
 4;119,121,4,1;,
 4;110,112,121,119;,
 4;121,122,6,4;,
 4;112,113,122,121;,
 4;122,123,8,6;,
 4;113,114,123,122;,
 4;123,124,10,8;,
 4;114,115,124,123;,
 4;124,125,12,10;,
 4;115,116,125,124;,
 4;125,126,14,12;,
 4;116,117,126,125;,
 4;117,118,127,126;,
 4;128,129,120,119;,
 4;130,128,119,1;,
 4;131,130,1,0;,
 4;129,128,130,131;,
 4;132,133,126,127;,
 4;134,135,16,14;,
 4;133,134,14,126;,
 4;133,132,135,134;,
 4;136,137,138,139;,
 4;140,136,139,141;,
 4;139,138,142,143;,
 4;141,139,143,144;;
 
 MeshMaterialList {
  5;
  94;
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
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
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
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  4,
  4,
  4,
  4;;
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
    "C:\\Users\\student\\Desktop\\mini_game\\Model\\foods\\texture\\pizza logo.png";
   }
  }
 }
 MeshNormals {
  98;
  -0.000132;0.177175;-0.984179;,
  0.855897;-0.198924;-0.477357;,
  0.915869;-0.401447;-0.005007;,
  0.703305;0.108887;0.702500;,
  0.000000;0.106394;0.994324;,
  -0.703305;0.108886;0.702500;,
  -0.973379;-0.209936;-0.091974;,
  -0.856238;-0.193773;-0.478862;,
  -0.000067;-0.008834;-0.999961;,
  0.732684;-0.040335;-0.679373;,
  0.998351;-0.057142;0.005488;,
  0.714642;-0.024197;0.699072;,
  0.000000;0.000000;1.000000;,
  -0.714642;-0.024197;0.699071;,
  -0.998375;-0.056747;0.005286;,
  -0.732609;-0.039753;-0.679488;,
  0.000000;-0.384551;-0.923104;,
  0.683030;-0.368289;-0.630740;,
  0.942339;-0.334661;-0.000000;,
  0.680529;-0.349467;0.644013;,
  0.000000;-0.341611;0.939842;,
  -0.680529;-0.349467;0.644013;,
  -0.942339;-0.334661;0.000000;,
  -0.683030;-0.368289;-0.630740;,
  0.000000;-0.709230;-0.704977;,
  0.518297;-0.695511;-0.497627;,
  0.739735;-0.672899;-0.000000;,
  0.518297;-0.695511;0.497627;,
  0.000000;-0.709230;0.704977;,
  -0.518297;-0.695511;0.497627;,
  -0.739735;-0.672899;0.000000;,
  -0.518297;-0.695511;-0.497627;,
  0.000000;-0.924736;-0.380610;,
  0.269132;-0.924736;-0.269132;,
  0.380610;-0.924736;-0.000000;,
  0.269132;-0.924736;0.269132;,
  0.000000;-0.924736;0.380610;,
  -0.269132;-0.924736;0.269132;,
  -0.380610;-0.924736;0.000000;,
  -0.269132;-0.924736;-0.269132;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;0.923450;-0.383718;,
  0.271330;0.923450;-0.271330;,
  0.383718;0.923450;0.000000;,
  0.271330;0.923450;0.271330;,
  0.000000;0.923450;0.383718;,
  -0.271330;0.923450;0.271330;,
  -0.383718;0.923450;0.000000;,
  -0.271330;0.923450;-0.271330;,
  -0.000013;0.734462;-0.678650;,
  0.500814;0.718144;-0.483171;,
  0.705094;0.709114;0.000000;,
  0.498577;0.709114;0.498577;,
  0.000000;0.709114;0.705094;,
  -0.498577;0.709114;0.498577;,
  -0.705094;0.709114;0.000000;,
  -0.500819;0.718167;-0.483132;,
  -0.000656;0.823945;-0.566670;,
  0.493161;0.723435;-0.483151;,
  0.625332;-0.780118;-0.019419;,
  0.392846;-0.831471;0.392846;,
  0.000000;-0.831471;0.555568;,
  -0.392846;-0.831471;0.392846;,
  -0.621988;-0.782809;-0.018461;,
  -0.857358;-0.467198;-0.216016;,
  0.000780;-0.979865;0.199661;,
  0.790089;-0.153249;-0.593527;,
  0.154093;-0.967934;0.198391;,
  -0.001211;0.952315;-0.305115;,
  0.255209;0.921091;-0.294042;,
  -0.257551;0.919878;-0.295791;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.854440;-0.473639;-0.213539;,
  0.828845;0.559478;0.000000;,
  0.586082;0.559478;0.586082;,
  0.000000;0.559478;0.828845;,
  -0.586082;0.559479;0.586082;,
  -0.541417;-0.810293;0.224262;,
  -0.828845;0.559479;0.000000;,
  -0.493805;0.722744;-0.483527;,
  -0.152552;-0.968623;0.196209;,
  -0.003747;-0.085160;-0.996360;,
  -0.792147;-0.156272;-0.589984;,
  0.005059;0.874596;-0.484826;,
  0.244812;0.843931;-0.477334;,
  -0.234991;0.854116;-0.463966;,
  0.005182;0.749950;-0.661474;,
  0.346355;0.703854;-0.620184;,
  -0.337955;0.705520;-0.622919;,
  0.005044;0.577185;-0.816598;,
  0.430463;0.528345;-0.731815;,
  -0.421336;0.516039;-0.745775;;
  94;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  3;32,33,40;,
  3;33,34,40;,
  3;34,35,40;,
  3;35,36,40;,
  3;36,37,40;,
  3;37,38,40;,
  3;38,39,40;,
  3;39,32,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  3;44,46,45;,
  3;44,47,46;,
  3;44,48,47;,
  3;44,49,48;,
  3;44,50,49;,
  3;44,51,50;,
  3;44,52,51;,
  3;44,45,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,45,53,60;,
  4;53,54,62,61;,
  4;78,63,2,1;,
  4;54,55,79,62;,
  4;63,64,64,2;,
  4;55,56,80,79;,
  4;64,65,65,64;,
  4;56,57,81,80;,
  4;65,66,66,65;,
  4;57,58,82,81;,
  4;66,67,83,66;,
  4;58,59,84,82;,
  4;67,68,7,6;,
  4;59,60,85,84;,
  4;60,53,61,85;,
  4;73,72,61,62;,
  4;70,70,78,1;,
  4;69,86,86,69;,
  4;87,70,70,87;,
  4;72,74,85,61;,
  4;71,69,69,71;,
  4;88,88,7,68;,
  4;88,87,87,88;,
  4;89,90,93,92;,
  4;91,89,92,94;,
  4;92,93,96,95;,
  4;94,92,95,97;;
 }
 MeshTextureCoords {
  145;
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
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
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  0.875000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.486601;5.972851;,
  0.919882;5.972851;,
  0.977668;6.393879;,
  0.486603;6.393879;,
  0.053322;5.972851;,
  -0.004463;6.393879;,
  1.067297;7.024001;,
  0.486603;7.024001;,
  -0.094094;7.024001;;
 }
}
