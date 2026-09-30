/* Address: ram:0004375a; name: FUN_ram_0004375a; body bytes: 68 */

undefined4 FUN_ram_0004375a(undefined4 param_1,int *param_2)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (*(ushort *)(param_2 + 1) < 2) {
    return 2;
  }
  if (*param_2 != 0) {
    uVar1 = FUN_ram_00041bf2(*param_2,1);
    uVar1 = FUN_ram_0004332a(param_1,&LAB_ram_000434f4,0xe,param_2,uVar1);
    return uVar1;
  }
  return 2;
}

