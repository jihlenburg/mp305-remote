/* Address: CODE:1d32; name: FUN_CODE_1d32; body bytes: 12 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

undefined1 FUN_CODE_1d32(undefined1 param_1,char param_2,byte param_3)

{
  DAT_EXTMEM_04d6 = param_3 & 3;
  DAT_EXTMEM_04d7 = param_1;
  return *(undefined1 *)
          (CONCAT11('\x03' - (((0xcU < (byte)(param_2 * '\x04')) << 7) >> 7),param_2 * '\x04' - 0xd)
          + 1);
}

