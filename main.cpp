#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
struct Cmp {
  bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
    if (a.first == b.first) {
      return (a.second < b.second);
    }
    return (a.first > b.first);
  }
};
struct Radio {
  std::multiset<std::pair<int, int>, Cmp> station_;
  std::unordered_map<int, int> proverka_;
  std::unordered_map<std::string, int> set_;
 public:
  Radio() {
    for (int i = 1; i < 100000; i++) {
      station_.emplace(0, i);
      proverka_.emplace(i, 0);
    }
  }
  std::pair<int, int> Get() {
    auto tmp1 = std::make_pair(station_.begin()->second, station_.begin()->first);
    proverka_.erase(proverka_.find(station_.begin()->second));
    int tmp = station_.begin()->second;
    station_.erase(station_.begin());
    station_.emplace(-1, tmp);
    proverka_.emplace(tmp, -1);
    return tmp1;
  }
  int Vote() {
    std::string ip;
    int time, track, score;
    std::cin >> ip >> track >> score >> time;
    if (proverka_.find(track) == proverka_.end()) {
      proverka_.emplace(track, 0);
      station_.emplace(0, track);
    }
    auto find = set_.find(ip);
    if (find != set_.end()) {
      if (time - find->second >= 600) {
        find->second = time;  //Нвдо проверить есть ли этот элемент в стайшне
        if (proverka_.find(track) != proverka_.end()) {
          int zen = proverka_.find(track)->second;
          if (station_.find(std::make_pair(zen, track)) != station_.end()) {
            station_.erase(station_.find(std::make_pair(zen, track)));
            station_.emplace(zen + score, track);
          }
          proverka_.erase(proverka_.find(track));
          proverka_.emplace(track, zen + score);
          return (zen + score);
        }
      } else {
        return proverka_.find(track)->second;
      }
    } else {
      set_.emplace(ip, time);
      int zen = proverka_.find(track)->second;
      proverka_.erase(proverka_.find(track));
      proverka_.emplace(track, zen + score);
      if (station_.find(std::make_pair(zen, track)) != station_.end()) {
        station_.erase(station_.find(std::make_pair(zen, track)));
        station_.emplace(zen + score, track);
        return (zen + score);
      }
    }
    return 0;
  }
  void Exit() const {
    std::cout << "OK" << '\n';
  }
};
int main() {
  Radio a;
  std::cout << a.station_.begin()->first << " " << a.station_.begin()->second << " ";
  std::string name;
  int k;
  std::cin >> k;
  for (int h = 0; h < k; h++) {
    std::cin >> name;
    if (name == "GET") {
      auto u = a.Get();
      std::cout << u.first << " " << u.second << '\n';
    }
    if (name == "VOTE") {
      std::cout << a.Vote() << '\n';
    }
    if (name == "EXIT") {
      a.Exit();
    }
  }
  return 0;
}
