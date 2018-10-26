(ns bsts.hw)

;; Problem 1

(defn prod1 [xx]
  (apply * xx))

(defn prod2 [xx]
  (reduce * 1 xx))

(defn prod3 [xx]
  (if (empty? xx) 1
    (* (first xx) (prod3 (rest xx)))))

;; Problem 2

(defn num-zeros [v]
  (cond (empty? v) 0
        (zero? (first v)) (+ 1 (num-zeros (rest v)))
        :otherwise        (num-zeros (rest v))))

(defn num-zeros-2 [v]
  (count (filter zero? v)))

(defn num-not-zeros-2 [v]
  (count (remove zero? v)))

;; Problem 4

(def sv [ {:name "Barny" :salary 123.33} {:name "Fred" :salary 1234423}])

(defn salary [sv n]
  (map :salary 
       (filter #(= n (:name %)) sv)))


