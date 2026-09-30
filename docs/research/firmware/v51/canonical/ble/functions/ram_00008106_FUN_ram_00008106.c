/* Address: ram:00008106; name: FUN_ram_00008106; body bytes: 90 */

undefined4 FUN_ram_00008106(undefined4 param_1,int param_2,undefined4 *param_3,uint *param_4)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_68 [4];
  uint uStack_64;
  
  gp = &DAT_ram_20002000;
  if (*(short *)(param_2 + 0xe) < 0) {
LAB_ram_0000811a:
    uVar1 = *(ushort *)(param_2 + 0xc);
    *param_4 = 0;
    if ((uVar1 & 0x80) != 0) {
      uVar3 = 0x40;
      goto LAB_ram_00008152;
    }
  }
  else {
    iVar2 = FUN_ram_00008c26(param_1,(int)*(short *)(param_2 + 0xe),auStack_68);
    if (iVar2 < 0) goto LAB_ram_0000811a;
    *param_4 = (uint)((uStack_64 & 0xf000) == 0x2000);
  }
  uVar3 = 0x400;
LAB_ram_00008152:
  *param_3 = uVar3;
  return 0;
}

