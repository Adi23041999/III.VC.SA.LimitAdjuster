#pragma once

#define INITSAVEBUF
#define VALIDATESAVEBUF(b)

inline void
SkipSaveBuf(uint8_t *&buf, int32_t skip)
{
	buf += skip;
}

template <typename T>
inline void
ReadSaveBuf(T* out, uint8_t *&buf)
{
	*out = *(T *)buf;
	SkipSaveBuf(buf, sizeof(T));
}

template <typename T>
inline T *
WriteSaveBuf(uint8_t *&buf, const T &value)
{
	T *p = (T *)buf;
	*p = value;
	SkipSaveBuf(buf, sizeof(T));
	return p;
}

#define SAVE_HEADER_SIZE (4 * sizeof(char) + sizeof(uint32_t))

#define WriteSaveHeader(buf, a, b, c, d, size) \
	WriteSaveBuf(buf, a); \
	WriteSaveBuf(buf, b); \
	WriteSaveBuf(buf, c); \
	WriteSaveBuf(buf, d); \
	WriteSaveBuf(buf, (uint32_t)(size));

#define CheckSaveHeader(buf, a, b, c, d, size) SkipSaveBuf(buf, 8);
