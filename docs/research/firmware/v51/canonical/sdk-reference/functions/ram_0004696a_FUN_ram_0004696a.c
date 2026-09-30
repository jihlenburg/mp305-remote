/* Address: ram:0004696a; name: FUN_ram_0004696a; body bytes: 670 */

int FUN_ram_0004696a(undefined4 param_1)

{
  int iVar1;
  byte bVar2;
  undefined2 uVar3;
  uint uVar4;
  undefined4 uVar5;
  char cVar6;
  char cStack_51;
  undefined2 auStack_50 [6];
  undefined2 auStack_44 [3];
  undefined2 auStack_3e [3];
  undefined2 auStack_38 [3];
  undefined2 auStack_32 [3];
  undefined2 auStack_2c [3];
  undefined2 auStack_26 [7];
  
  gp = 0x20004000;
  iVar1 = 0x12;
  if ((DAT_ram_20001d50 & 8) != 0) {
    iVar1 = 0x10;
    if (DAT_ram_20001a04 == 0) {
      uVar4 = thunk_FUN_ram_0004e07e();
      iVar1 = 0x15;
      if (uVar4 < DAT_ram_20001d54) {
        iVar1 = 0x11;
        if (DAT_ram_200019e0 == 0) {
          DAT_ram_200019e0 = FUN_ram_20000040(10,0x471c);
          iVar1 = 0x13;
          if (DAT_ram_200019e0 != 0) {
            tmos_memcpy(DAT_ram_200019e0,param_1,10);
            bVar2 = GAP_GetParamValue(0x26);
            iVar1 = 0x18;
            if ((bVar2 & 5) != 0) {
              tmos_memset(auStack_50,0,0x30);
              iVar1 = 0;
              if ((bVar2 & 1) != 0) {
                auStack_44[0] = GAP_GetParamValue(0x10);
                auStack_3e[0] = GAP_GetParamValue(0xf);
                auStack_38[0] = GAP_GetParamValue(0xd);
                auStack_32[0] = GAP_GetParamValue(0xe);
                auStack_2c[0] = GAP_GetParamValue(8);
                auStack_26[0] = GAP_GetParamValue(7);
                if (*(char *)(DAT_ram_200019e0 + 1) == '\0') {
                  auStack_50[0] = GAP_GetParamValue(9);
                  uVar5 = 10;
                }
                else {
                  auStack_50[0] = GAP_GetParamValue(0xb);
                  uVar5 = 0xc;
                }
                auStack_50[3] = GAP_GetParamValue(uVar5);
                iVar1 = 1;
              }
              uVar3 = GAP_GetParamValue(0x2c);
              auStack_50[iVar1 + 6] = uVar3;
              uVar3 = GAP_GetParamValue(0x2b);
              auStack_50[iVar1 + 9] = uVar3;
              uVar3 = GAP_GetParamValue(0x29);
              auStack_50[iVar1 + 0xc] = uVar3;
              uVar3 = GAP_GetParamValue(0x2a);
              auStack_50[iVar1 + 0xf] = uVar3;
              uVar3 = GAP_GetParamValue(0x28);
              auStack_50[iVar1 + 0x12] = uVar3;
              uVar3 = GAP_GetParamValue(0x27);
              auStack_50[iVar1 + 0x15] = uVar3;
              if ((bVar2 & 4) != 0) {
                uVar3 = GAP_GetParamValue(0x36);
                auStack_50[iVar1 + 7] = uVar3;
                uVar3 = GAP_GetParamValue(0x35);
                auStack_50[iVar1 + 10] = uVar3;
                uVar3 = GAP_GetParamValue(0x33);
                auStack_50[iVar1 + 0xd] = uVar3;
                uVar3 = GAP_GetParamValue(0x34);
                auStack_50[iVar1 + 0x10] = uVar3;
                uVar3 = GAP_GetParamValue(0x2e);
                auStack_50[iVar1 + 0x13] = uVar3;
                uVar3 = GAP_GetParamValue(0x2d);
                auStack_50[iVar1 + 0x16] = uVar3;
                if (*(char *)(DAT_ram_200019e0 + 1) == '\0') {
                  uVar3 = GAP_GetParamValue(0x2f);
                  auStack_50[iVar1 + 1] = uVar3;
                  uVar5 = 0x30;
                }
                else {
                  uVar3 = GAP_GetParamValue(0x31);
                  auStack_50[iVar1 + 1] = uVar3;
                  uVar5 = 0x32;
                }
                uVar3 = GAP_GetParamValue(uVar5);
                auStack_50[iVar1 + 4] = uVar3;
              }
              uVar5 = FUN_ram_000442de(*(undefined1 *)(DAT_ram_200019e0 + 3),DAT_ram_200019e0 + 4);
              GAPBondMgr_GetParameter(0x41f,&cStack_51);
              cVar6 = DAT_ram_20001c06 != '\0';
              if (cStack_51 != '\0') {
                cVar6 = cVar6 + '\x02';
              }
              iVar1 = thunk_FUN_ram_0006596e
                                (*(undefined1 *)(DAT_ram_200019e0 + 2),cVar6,uVar5,
                                 DAT_ram_200019e0 + 4,bVar2 | 2,auStack_50,auStack_50 + 3,auStack_26
                                 ,auStack_2c,auStack_32,auStack_38,auStack_50 + 9,auStack_50 + 6);
              if (iVar1 != 0) {
                FUN_ram_00044f96(3);
              }
            }
          }
        }
      }
    }
  }
  return iVar1;
}

