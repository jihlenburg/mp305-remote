/* Address: ram:000402b0; name: FUN_ram_000402b0; body bytes: 196 */

int FUN_ram_000402b0(int param_1,uint param_2)

{
  ushort uVar1;
  ushort uVar2;
  int *piVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 uVar6;
  
  gp = 0x20004000;
  if (param_1 == 0) {
    return 0;
  }
  if (param_2 != 0) {
    uVar2 = (ushort)(param_1 + 3U) & 0xfffc;
    uVar5 = param_1 + 3U & 0xfffc;
    piVar3 = DAT_ram_20001b58;
    if (uVar5 < 0x35) {
      piVar3 = DAT_ram_20001b5c;
    }
    for (; (int *)DAT_ram_20001b54 != piVar3; piVar3 = (int *)*piVar3) {
      if (*(short *)((int)piVar3 + 6) == 0) {
        uVar1 = *(ushort *)(piVar3 + 1);
        if (uVar5 <= uVar1) {
          if (8 < uVar1 - uVar5) {
            uVar6 = *piVar3;
            puVar4 = (undefined4 *)(uVar5 + 8 + (int)piVar3);
            *(ushort *)(puVar4 + 1) = (uVar1 - uVar2) + -8;
            *puVar4 = uVar6;
            *(undefined2 *)((int)puVar4 + 6) = 0;
            *piVar3 = (int)puVar4;
            *(ushort *)(piVar3 + 1) = uVar2;
            DAT_ram_20001b6a = DAT_ram_20001b6a + -8;
          }
          *(short *)((int)piVar3 + 6) = (short)param_2;
          DAT_ram_20001b6a = DAT_ram_20001b6a - uVar2;
          return (int)(piVar3 + 2);
        }
      }
    }
    if (DAT_ram_20001bec != (code *)0x0) {
      (*DAT_ram_20001bec)(1,param_2 | uVar5 << 0x10);
      return 0;
    }
  }
  return 0;
}

