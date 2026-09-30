/* Address: 00046c74; name: FUN_00046c74; body bytes: 38 */

undefined4 FUN_00046c74(uint param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_0004a118();
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    if (*(byte *)*puVar1 == param_1) break;
    puVar1 = (undefined4 *)FUN_0004a13c(&DAT_2003a5f0);
  }
  return *puVar1;
}

