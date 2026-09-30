/* Address: ram:00002dfe; name: FUN_ram_00002dfe; body bytes: 32 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00002dfe(undefined4 param_1,int param_2,undefined4 param_3,undefined2 *param_4,
                     undefined4 param_5)

{
  undefined2 *unaff_s1;
  undefined8 uVar1;
  
  gp = &DAT_ram_20002000;
  uVar1 = (**(code **)(DAT_ram_20002f64 + 4))
                    (param_1,*(undefined4 *)(param_2 + 0xc),*param_4,param_4,param_5,
                     *(code **)(DAT_ram_20002f64 + 4));
  FUN_ram_00002dea((int)uVar1,(int)((ulonglong)uVar1 >> 0x20),*unaff_s1);
  return;
}

