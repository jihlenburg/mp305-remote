/* Address: 0003df98; name: FUN_0003df98; body bytes: 28 */

void FUN_0003df98(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 0xc);
  UNRECOVERED_JUMPTABLE = (code *)*puVar1;
  uVar2 = puVar1[1];
  FUN_000528ac();
  FUN_00046bec(puVar1);
                    /* WARNING: Could not recover jumptable at 0x0003dfb2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(uVar2);
  return;
}

