#include <DailyTask/daily_task_16.h>

void readInput(std::string& transmission)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_16_input.txt");
  std::string input;
  file >> input;
  file.close();

  transmission = "";
  for (char c : input)
  {
    transmission += getBinFromHex(c);
  }
}

Packet getNextLiteral(const std::string& transmission, int pos, int length)
{
  Packet literal;
  std::string l = "";
  int i = 0;

  while (i < length)
  {
    l += transmission.substr(pos + i + 1, 4);
    i += 5;
  }

  literal.value = std::stoull(l, 0, 2);

  return literal;
}

long getPacketValue(const Packet& packet)
{
  if (packet.type_id == 0)
  {
    long sum = 0;
    for (const Packet& p : packet.subpackets)
    {
      sum += p.value;
    }
    return sum;
  }

  if (packet.type_id == 1)
  {
    long prod = 1;
    for (const Packet& p : packet.subpackets)
    {
      prod *= p.value;
    }
    return prod;
  }

  if (packet.type_id == 2)
  {
    long min = std::numeric_limits<long>::max();
    for (const Packet& p : packet.subpackets)
    {
      min = std::min(p.value, min);
    }
    return min;
  }

  if (packet.type_id == 3)
  {
    long max = 0;
    for (const Packet& p : packet.subpackets)
    {
      max = std::max(p.value, max);
    }
    return max;
  }

  if (packet.type_id == 5)
  {
    return packet.subpackets[0].value > packet.subpackets[1].value;
  }

  if (packet.type_id == 6)
  {
    return packet.subpackets[0].value < packet.subpackets[1].value;
  }

  if (packet.type_id == 7)
  {
    return packet.subpackets[0].value == packet.subpackets[1].value;
  }

  else return packet.value;
}

void readTransmission(const std::string& transmission, int& pos, Packet& mother_packet)
{
  if (pos + 3 >= transmission.length()) return;

  if (mother_packet.operator_id == 1 && mother_packet.subpackets.size() >= mother_packet.length) return;

  std::bitset<3> version = std::bitset<3>(transmission.substr(pos, 3));
  pos += 3;
  std::bitset<3> type_id = std::bitset<3>(transmission.substr(pos, 3));
  pos += 3;

  if (type_id == 4)
  {
    int length = 0;
    while (transmission.at(pos + length) != '0')
    {
      length += 5;
    }
    length += 5;
    Packet literal = getNextLiteral(transmission, pos, length);
    literal.type_id = type_id.to_ulong();
    literal.version = version.to_ulong();

    mother_packet.subpackets.push_back(literal);
    pos += length;
  }
  else
  {
    int identifier = std::stoull(transmission.substr(pos, 1), 0, 2);
    pos += 1;
    if (identifier == 0)
    {
      Packet op;
      op.version = version.to_ulong();
      op.type_id = type_id.to_ulong();
      op.operator_id = 0;
      op.length = std::stoull(transmission.substr(pos, 15), 0, 2);
      pos += 15;
      int new_pos = 0;
      std::string sub_transmission = transmission.substr(pos, op.length);
      readTransmission(sub_transmission, new_pos, op);
      pos += new_pos;
      op.value = getPacketValue(op);
      mother_packet.subpackets.push_back(op);
    }
    else
    {
      Packet op;
      op.version = version.to_ulong();
      op.type_id = type_id.to_ulong();
      op.operator_id = 1;
      op.length = std::stoull(transmission.substr(pos, 11), 0, 2);
      pos += 11;
      int subpacket_count = op.length;
      while (subpacket_count > 0)
      {
        readTransmission(transmission, pos, op);
        subpacket_count--;
      }
      op.value = getPacketValue(op);
      mother_packet.subpackets.push_back(op);
    }
  }
  readTransmission(transmission, pos, mother_packet);
}

void getSum(int& sum, const Packet& packet)
{
  for (const Packet& p: packet.subpackets)
  {
    sum += p.version;
    getSum(sum, p);
  }
}


void DailyTask16::part1()
{
  std::string transmission;
  readInput(transmission);

  Packet mother_packet;
  int pos = 0;
  readTransmission(transmission, pos, mother_packet);

  int sum = 0;
  getSum(sum, mother_packet);

  std::cout <<"PART1 : sum: "<<sum<<std::endl;
}

void DailyTask16::part2()
{
  std::string transmission;
  readInput(transmission);

  Packet mother_packet;
  int pos = 0;
  readTransmission(transmission, pos, mother_packet);

  std::cout <<"PART2 : result: "<<mother_packet.subpackets.front().value<<std::endl;
}

int main() {

  DailyTask16 dt16("Day 16: Packet Decoder");
  dt16.part1();
  dt16.part2();

  return 0;
}