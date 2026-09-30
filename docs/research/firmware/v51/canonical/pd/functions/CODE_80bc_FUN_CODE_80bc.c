/* Address: CODE:80bc; name: FUN_CODE_80bc; body bytes: 61 */

void FUN_CODE_80bc(undefined1 *param_1)

{
  FUN_CODE_9d61();
  DAT_INTMEM_cb = FUN_CODE_a934();
  FUN_CODE_43f1();
  DAT_INTMEM_ca = *param_1;
  FUN_CODE_4482();
  DAT_INTMEM_cc = *param_1;
  DAT_INTMEM_cd =
       *(undefined1 *)
        CONCAT11('\x05' - (((0x13 < DAT_INTMEM_b3 * '\x04') << 7) >> 7),
                 DAT_INTMEM_b3 * '\x04' - 0x14);
  _0_2 = (&DAT_CODE_b84d)[DAT_INTMEM_b3] != '\0';
  return;
}

