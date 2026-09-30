/* Address: CODE:af51; name: FUN_CODE_af51; body bytes: 25 */

void FUN_CODE_af51(byte param_1)

{
  undefined1 *puVar1;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  puVar1 = (undefined1 *)CONCAT11(uStackX_0,in_stack_000000ff);
  *(undefined1 *)(ushort)param_1 = *puVar1;
  *(undefined1 *)(ushort)(param_1 + 1) = puVar1[1];
  *(undefined1 *)(ushort)(param_1 + 2) = puVar1[2];
  *(undefined1 *)(ushort)(param_1 + 3) = puVar1[3];
                    /* WARNING: Could not recover jumptable at 0xaf69. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(puVar1 + 4))();
  return;
}

