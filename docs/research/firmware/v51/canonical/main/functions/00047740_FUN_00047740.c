/* Address: 00047740; name: FUN_00047740; body bytes: 28 */

undefined4 FUN_00047740(int *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  code *pcVar2;
  
  uVar1 = 0;
  pcVar2 = *(code **)(*param_1 + 8);
  if (pcVar2 != (code *)0x0) {
    uVar1 = (*pcVar2)(*param_1,param_1,param_2,param_3);
  }
  return uVar1;
}

