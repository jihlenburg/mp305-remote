/* Address: CODE:3724; name: FUN_CODE_3724; body bytes: 218 */

undefined1 FUN_CODE_3724(char param_1,char param_2)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  
  cVar1 = FUN_CODE_88fd(0x739);
  bVar2 = FUN_CODE_88f5(cVar1 + '\x11');
  DAT_EXTMEM_073a = bVar2 & 0x7f;
  bVar2 = FUN_CODE_88f5(param_1 + '\x12');
  DAT_EXTMEM_073b = bVar2 & 0x7f;
  DAT_EXTMEM_2155 = 0x10;
  DAT_EXTMEM_2154 = 4;
  cVar1 = FUN_CODE_88fd(0x73c);
  bVar2 = FUN_CODE_88f5(cVar1 + '\x14');
  DAT_EXTMEM_073d = bVar2 & 0x7f;
  bVar2 = FUN_CODE_88f5(param_1 + '\x15');
  DAT_EXTMEM_073e = bVar2 & 0x7f;
  DAT_EXTMEM_2255 = 0x10;
  cVar1 = FUN_CODE_8911(4,&UNK_CODE_2254);
  cVar1 = FUN_CODE_8909(cVar1 + '\x16');
  DAT_EXTMEM_203c = -0x3d;
  if (cVar1 != '\0') {
    DAT_EXTMEM_203c = cVar1;
  }
  cVar3 = FUN_CODE_8909(param_2 + '\x17');
  cVar1 = -0x69;
  if (cVar3 != '\0') {
    cVar1 = cVar3;
  }
  cVar3 = FUN_CODE_8911(cVar1,0x203d);
  cVar3 = FUN_CODE_8909(cVar3 + '\x18');
  if (cVar3 == '\0') {
    cVar3 = 'C';
  }
  DAT_EXTMEM_203e = cVar3;
  cVar4 = FUN_CODE_8900();
  bVar2 = FUN_CODE_88f5(cVar4 + '\x1f');
  DAT_EXTMEM_2020 = bVar2 & 3;
  DAT_EXTMEM_2021 = FUN_CODE_88f5(cVar3 + ' ');
  cVar4 = FUN_CODE_8900();
  bVar2 = FUN_CODE_88f5(cVar4 + '\x19');
  DAT_EXTMEM_0737 = bVar2 & 0x3f;
  DAT_EXTMEM_2304 = DAT_EXTMEM_0737 + 3;
  bVar2 = FUN_CODE_88f5(cVar3 + '\x1a');
  DAT_EXTMEM_0738 = bVar2 & 0x3f;
  DAT_EXTMEM_2404 = DAT_EXTMEM_0738 + 3;
  FIE1 = 0;
  cVar1 = FUN_CODE_8909(cVar1 + '(');
  if (cVar1 != '\0') {
    FIE1 = 0x2e;
    FIE1 = 0;
    DAT_EXTMEM_1053 = cVar1;
  }
  return 0;
}

