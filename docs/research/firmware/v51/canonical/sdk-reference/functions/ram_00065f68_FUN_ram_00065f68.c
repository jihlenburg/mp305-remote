/* Address: ram:00065f68; name: FUN_ram_00065f68; body bytes: 254 */

undefined4 FUN_ram_00065f68(int param_1)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  ushort uVar5;
  
  gp = 0x20004000;
  if ((DAT_ram_20001db4 == 0) || (-1 < *(int *)(DAT_ram_20001db4 + 0x54) << 4)) {
    if (DAT_ram_20001dc4 != (code *)0x0) {
      if (param_1 == 0) {
        iVar3 = FUN_ram_00054de4(0xf0);
        if ((iVar3 != 0) && (*(char *)(iVar3 + 0xc) != '\0')) {
          FUN_ram_0005501c();
          gp = 0x20004000;
          return 0;
        }
      }
      else if (param_1 == 1) {
        iVar3 = DAT_ram_20001db4;
        if (DAT_ram_20001db4 == 0) {
          iVar3 = (*DAT_ram_20001dc4)(0);
          if (iVar3 == 0) {
            gp = 0x20004000;
            return 7;
          }
          *(undefined2 *)(iVar3 + 0x20) = 0x800;
          *(undefined2 *)(iVar3 + 0xe) = 0x700;
          *(undefined1 *)(iVar3 + 0x18) = 3;
          *(undefined1 *)(iVar3 + 0x35) = 0;
          tmos_memcpy(iVar3 + 0x36,&DAT_ram_20001e38,6);
        }
        if ((*(char *)(iVar3 + 0xc) != '\x01') &&
           (((*(byte *)(iVar3 + 0xe) & 0xe) != 0 ||
            (uVar4 = FUN_ram_00055ed6(), uVar4 != (DAT_ram_20001bd3 & 3))))) {
          if (*(char *)(iVar3 + 0xe) == '\x01') {
            *(undefined2 *)(iVar3 + 0x20) = 2;
          }
          else {
            uVar1 = *(ushort *)(iVar3 + 0x20);
            uVar5 = 0x4000;
            if ((uVar1 < 0x4001) && (uVar5 = uVar1, uVar1 < 0x20)) {
              uVar5 = 0x20;
            }
            *(ushort *)(iVar3 + 0x20) = uVar5;
          }
                    /* WARNING: Could not recover jumptable at 0x00066028. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          uVar2 = (*DAT_ram_20001dc8)(0xf0);
          return uVar2;
        }
      }
    }
    uVar2 = 0x12;
  }
  else {
    uVar2 = 0xc;
  }
  return uVar2;
}

