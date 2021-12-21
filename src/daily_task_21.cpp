#include <DailyTask/daily_task_21.h>

void readInput(int& pl1_start, int& pl2_start)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_21_input.txt");
  std::string line;

  std::getline(file, line);
  pl1_start = stoi(line.substr(line.size()-1));

  std::getline(file, line);
  pl2_start = stoi(line.substr(line.size()-1));

  file.close();
}

void playDiracGame(const int final_score, int pl1_start, int pl2_start, long& pl1_wins, long& pl2_wins)
{
  Game first_game_state(pl1_start, pl2_start);

  std::unordered_map<Game, long, Game::GameHasher> game_states_counter;
  std::unordered_map<Game, std::vector<Game>, Game::GameHasher> game_states;
  pl1_wins = 0;
  pl2_wins = 0;

  game_states_counter[first_game_state] = 1;
  bool all_games_finished = false;

  while (!all_games_finished)
  {
    std::unordered_map<Game, long, Game::GameHasher> next_gs_counter;
    all_games_finished = true;

    for (const auto&[game_state, count]: game_states_counter)
    {
      if (game_states.find(game_state) == game_states.end())
      {
        game_states[game_state] = game_state.getNextDiracGameStates();
      }

      for (const Game& next_state : game_states[game_state])
      {
        if (next_state.player1_score >= final_score || next_state.player2_score >= final_score)
        {
          if (next_state.player1_score > next_state.player2_score)
          {
            pl1_wins += count;
          }
          else
          {
            pl2_wins += count;
          }
        }
        else
        {
          all_games_finished = false;
          next_gs_counter[next_state] += count;
          }
        }
    }

    game_states_counter = next_gs_counter;
  }
}

void DailyTask21::part1()
{
  int pl1_start;
  int pl2_start;
  readInput(pl1_start, pl2_start);

  Game game(pl1_start, pl2_start);

  game.playGame(1000);

  int losing_score = std::min(game.player2_score, game.player1_score);

  std::cout<<"PART1: result: "<<losing_score * game.roll_count<<std::endl;
}

void DailyTask21::part2()
{
  int pl1_start;
  int pl2_start;
  readInput(pl1_start, pl2_start);

  long pl1_wins = 0;
  long pl2_wins = 0;

  playDiracGame(21, pl1_start, pl2_start, pl1_wins, pl2_wins);

  std::cout<<"PART2: result: "<<std::max(pl1_wins, pl2_wins)<<std::endl;
}

int main() {

  DailyTask21 dt21("Day 21: Dirac Dice");
  dt21.part1();
  dt21.part2();

  return 0;
}