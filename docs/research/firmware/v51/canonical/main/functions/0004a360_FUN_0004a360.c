/* Address: 0004a360; name: FUN_0004a360; body bytes: 34 */

undefined4 * FUN_0004a360(int param_1)

{
  undefined4 *puVar1;
  
  if (param_1 == 0) {
    return &DAT_2003a484;
  }
  puVar1 = (undefined4 *)FUN_0004a328();
  if (puVar1 != (undefined4 *)0x0) {
    FUN_0004a57a(puVar1,0,param_1);
    return puVar1;
  }
  return (undefined4 *)0x0;
}

