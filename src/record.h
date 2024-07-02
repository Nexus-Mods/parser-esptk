#ifndef RECORD_H
#define RECORD_H

#include <cstdint>
#include <vector>
#include <istream>

#if !defined(_WIN32)
#include <cstring>
#endif

namespace ESP {

/**
 * @brief record storage class without record-specific information
 */
class Record
{
public:
  enum EFlag {
    FLAG_MASTER     = 0x00000001,
    FLAG_LOCALIZED  = 0x00000080,
    SF_FLAG_LIGHT   = 0x00000100,
    FLAG_LIGHT      = 0x00000200,
    FLAG_MEDIUM     = 0x00000400,
    FLAG_COMPRESSED = 0x00040000,
  };

public:
  Record();

  size_t size() const;

  bool readFrom(std::istream &stream);
  void writeTo(std::ostream &stream);

  bool flagSet(EFlag flag) const;
  void setFlag(EFlag flag, bool enable);

  const std::vector<uint8_t> &data() const { return m_Data; }

  uint32_t revision() const { return *(reinterpret_cast<const uint32_t*>(m_VersionInfo)); }

private:

private:
  struct Header {
    char type[4];
    uint32_t dataSize;
    uint32_t flags;
    uint32_t id;
    uint32_t revision;
  } m_Header;

  char m_VersionInfo[4];

  std::vector<uint8_t> m_Data;

  bool m_OblivionStyle;
};

}

#endif // RECORD_H
