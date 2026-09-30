/* Address: 00050a14; name: thunk_FUN_00050a1a; body bytes: 2 */

int thunk_FUN_00050a1a(byte *param_1,byte *param_2)

{
  byte bVar1;
  
  while( true ) {
    bVar1 = *param_1;
    if ((bVar1 == 0) || (bVar1 != *param_2)) break;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  }
  return (uint)bVar1 - (uint)*param_2;
}

