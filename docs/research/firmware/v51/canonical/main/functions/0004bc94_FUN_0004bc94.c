/* Address: 0004bc94; name: FUN_0004bc94; body bytes: 16 */

undefined4 FUN_0004bc94(int param_1)

{
  undefined8 uVar1;
  
  do {
    uVar1 = FUN_0004bc8c(param_1,param_1);
    param_1 = (int)uVar1;
  } while (param_1 != 0);
  return (int)((ulonglong)uVar1 >> 0x20);
}

