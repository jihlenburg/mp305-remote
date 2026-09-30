/* Address: ram:0006632a; name: FUN_ram_0006632a; body bytes: 370 */

undefined4
FUN_ram_0006632a(undefined4 param_1,uint param_2,uint param_3,uint param_4,uint param_5,
                undefined2 param_6,undefined2 param_7)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  
  gp = 0x20004000;
  iVar3 = FUN_ram_00057ba2();
  uVar1 = 0x12;
  if ((((((iVar3 != 0) && (uVar1 = 0x12, (param_2 - 6 & 0xffff) < 0xc7b)) && (param_3 < 0xc81)) &&
       ((param_2 <= param_3 && (param_4 < 500)))) &&
      ((param_5 < 0xc81 &&
       (((int)((param_4 + 1) * param_2) < (int)(param_5 << 3) &&
        (uVar1 = 0xc, (*(byte *)(iVar3 + 0x11) & 1) == 0)))))) &&
     ((*(uint *)(iVar3 + 0xa4) & 0x201) == 0)) {
    *(short *)(iVar3 + 0x5a) = (short)param_5;
    *(undefined2 *)(iVar3 + 0x76) = param_6;
    *(short *)(iVar3 + 0x72) = (short)param_2;
    *(short *)(iVar3 + 0x74) = (short)param_3;
    *(undefined2 *)(iVar3 + 0x78) = param_7;
    *(short *)(iVar3 + 0x58) = (short)param_4;
    uVar1 = 0;
    if (*(char *)(iVar3 + 0xb) == '\0') {
      if (*(char *)(iVar3 + 0x1d) == '\0') {
        if ((*(uint *)(iVar3 + 0x100) & 2) == 0) {
          if (param_2 == param_3) {
            *(short *)(iVar3 + 0x56) = (short)param_2;
          }
          else {
            uVar2 = FUN_ram_00042910(param_2,param_3 + param_2 >> 1);
            *(undefined2 *)(iVar3 + 0x56) = uVar2;
            FUN_ram_00052694(param_3,iVar3 + 0x56);
          }
          cVar4 = '\x04';
          if (DAT_ram_20001e04 < 4) {
            cVar4 = (char)DAT_ram_20001e04 + '\x01';
          }
          *(char *)(iVar3 + 0x53) = cVar4;
          FUN_ram_00055ef4(iVar3);
          *(short *)(iVar3 + 0x5c) = *(short *)(iVar3 + 0x3e) + 10;
          uVar5 = *(uint *)(iVar3 + 0xa4) | 1;
        }
        else {
          tmos_memset(iVar3 + 0x66,0xff,0xc);
          *(undefined2 *)(iVar3 + 0x66) = 0;
          uVar5 = *(uint *)(iVar3 + 0xa4) | 0x200;
        }
        *(uint *)(iVar3 + 0xa4) = uVar5;
        *(undefined1 *)(iVar3 + 0x1d) = 0x12;
        uVar1 = 0;
      }
    }
    else if (*(char *)(iVar3 + 0x1d) == '\0') {
      if ((*(uint *)(iVar3 + 0x108) & 2) == 0) {
        uVar1 = 0x1a;
      }
      else {
        tmos_memset(iVar3 + 0x66,0xff,0xc);
        *(undefined2 *)(iVar3 + 0x66) = 0;
        *(uint *)(iVar3 + 0xa4) = *(uint *)(iVar3 + 0xa4) | 0x200;
        *(undefined1 *)(iVar3 + 0x1d) = 0x13;
      }
    }
  }
  return uVar1;
}

