/* Address: ram:000437d2; name: FUN_ram_000437d2; body bytes: 36 */

undefined4 FUN_ram_000437d2(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if ((*(char *)(param_2 + 4) != '\x02') && (*(char *)(param_2 + 4) != '\x10')) {
    return 2;
  }
  uVar1 = FUN_ram_0004332a(param_1,&LAB_ram_0004355a,0x10,param_2,0);
  return uVar1;
}

