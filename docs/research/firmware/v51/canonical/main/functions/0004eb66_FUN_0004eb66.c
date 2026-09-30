/* Address: 0004eb66; name: FUN_0004eb66; body bytes: 72 */

uint FUN_0004eb66(int param_1,undefined4 param_2,uint param_3)

{
  char cVar1;
  int *piVar2;
  uint local_14;
  
  local_14 = param_3;
  if (((param_1 != 0) && (piVar2 = (int *)FUN_0004c924(param_1,param_2,0x61), piVar2 != (int *)0x0))
     && (*piVar2 != 0)) {
    cVar1 = FUN_0004c924(param_1,param_2,0x62);
    if (cVar1 != '\0') {
      local_14 = (*(code *)*piVar2)(piVar2,param_3);
      local_14 = local_14 & 0xffffff;
    }
  }
  return local_14;
}

