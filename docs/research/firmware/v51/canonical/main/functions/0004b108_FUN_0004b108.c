/* Address: 0004b108; name: FUN_0004b108; body bytes: 32 */

char FUN_0004b108(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = FUN_0004c924(param_1,param_2,0x5e);
  FUN_0004c924(param_1,param_2,0x27);
  if (cVar1 == '\0') {
    cVar1 = '\x01';
  }
  return cVar1;
}

